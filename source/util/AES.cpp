#include <util/AES.h>
#include <external/aes/AES.h>
#include <lang/Object.h>
#include <lang/Exception.h>

using namespace lang;

namespace util
{

class AES::Impl :
	public Object
{
public:
	Impl(const std::vector<unsigned char> & key, KeyLengthBits keyLength, PadMode pad)
	{
		unsigned char padding = pad;
		m_key = key;
		m_padMode = pad;
		unsigned int keybits = 8 * key.size();
		switch (keyLength)
		{
		case KEY_LENGTH_AUTODETECT:
		{
			if (keybits != 128 && keybits != 192 && keybits != 256)
				throwError(Exception(Format("Key length ({0}) is not either 16, 24 or 32 octets", key.size())));
		}
		case KEY_LENGTH_128: keybits = 128; break;
		case KEY_LENGTH_192: keybits = 192; break;
		case KEY_LENGTH_256: keybits = 256; break;
		default: throwError(Exception(Format("Unexpected KeyLengthBits value")));
		}
		if (key.size() != keybits >> 3)
			throwError(Exception(Format("Invalid key length for decrypter: {0}, expected: {1}", keyLength, keyLength >> 3))); //32, 32
		m_engine.SetParameters(keybits);
	}
	~Impl()
	{
	}
	void encrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out)
	{
		int paddingsize = end - begin;
		int sizerounded = BLOCK_SIZE - (paddingsize & 0xF);

		std::vector<unsigned char> inpadded;
		inpadded.assign(begin, end);
		inpadded.reserve(sizerounded + paddingsize);
		if (m_padMode == PAD_MODE_NOPAD)
		{
			if (paddingsize & 0xF)
				throwError(Exception(Format("Encryption with PadMode = PAD_MODE_NOPAD requires input size to be multiple of BLOCK_SIZE")));
			out.resize(paddingsize, 0);
			m_engine.StartEncryption(m_key.data());
			m_engine.Encrypt(begin, out.data(), out.size() >> 4);
		}
		else
		{
			if (m_padMode == PAD_MODE_FIPS81)
			{
				for (int i = 0; i < sizerounded - 1; i++)
					inpadded.push_back(rand() - rand() - 0x1000000);
				inpadded.push_back(sizerounded);
			}
			else
			{
				for (int i = 0; i < sizerounded; i++)
					inpadded.push_back(sizerounded);
			}
		}
		out.resize(sizerounded + paddingsize, 0);
		m_engine.StartEncryption(m_key.data());
		m_engine.Encrypt(inpadded.data(), out.data(), ((sizerounded + paddingsize) >> 4));
	}

	bool decrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out) //Correct? Do we use *.data()?
	{
		unsigned char padding = end - begin;
		if (m_padMode == PAD_MODE_NOPAD)
		{
			if (padding & 0xF)
				return false;
			else
			{
				out.resize(padding, 0);
				if (padding)
				{
					m_engine.StartDecryption(m_key.data()); //?
					m_engine.Decrypt(begin, out.data(), (padding >> 4)); //?
				}
				return true;
			}
		}
		else if (!padding || (padding & 0xF))
			return false;
		else
		{
			out.resize(padding);
			m_engine.StartDecryption(m_key.data());
			m_engine.Decrypt(begin, out.data(), (padding >> 4)); //?
			if (out.back() <= BLOCK_SIZE && (out.size() - out.back()) >= 0)
			{
				out.resize(out.size() - out.back());
				return true;
			}
			else
				return false;
		}
	}
	
private:
	::AES m_engine;
	std::vector<unsigned char> m_key;
	PadMode m_padMode;
};

AES::AES(const std::vector<unsigned char>& key, KeyLengthBits keyLength, PadMode pad)
{
	m_impl = new Impl(key, keyLength, pad);
}

AES::~AES()
{
}

void AES::encrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out)
{
	m_impl->encrypt(begin, end, out);
}

bool AES::decrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out)
{
	return m_impl->decrypt(begin, end, out);
}

void AES::encrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out)
{
	if (!in.empty()) //According to DWARF this is split by a line
		encrypt(in.data(), out.data(), out);
}

bool AES::decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out)
{
	if (!in.empty()) //According to DWARF this is split by a line
		return decrypt(in.data(), out.data(), out);
	return true;
}

}