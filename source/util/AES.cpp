#include <util/AES.h>
#include <external/aes/AES.h>
#include <lang/Object.h>
#include <lang/Exception.h>

using namespace lang;

namespace util
{

class AES::Impl : //15
	public Object
{
public:
	Impl(const std::vector<unsigned char> & key, KeyLengthBits keyLength, PadMode pad) : //19-49
		m_key(key),
		m_padMode(pad)
	{
		unsigned int keybits = 8 * key.size(); //23
		switch (keyLength)
		{
		case KEY_LENGTH_AUTODETECT:
		{
			if (keybits != 128 && keybits != 192 && keybits != 256)
				throwError(Exception(Format("Key length ({0}) is not either 16, 24 or 32 octets", key.size()))); //29
		}
		case KEY_LENGTH_128: keybits = 128; break;
		case KEY_LENGTH_192: keybits = 192; break;
		case KEY_LENGTH_256: keybits = 256; break;

		default: throwError(Exception(Format("Unexpected KeyLengthBits value"))); //41
		}

		if (key.size() != keybits >> 3)
			throwError(Exception(Format("Invalid key length for decrypter: {0}, expected: {1}", key.size(), keyLength >> 3))); //46 | 32, 32

		m_engine.SetParameters(keybits); //48
	}

	~Impl() //51
	{
		//if (m_key.begin() != m_key.end()) //54
			//m_key.clear();
	}

	void encrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out) //57
	{
		if (m_padMode == PAD_MODE_NOPAD)
		{
			if (end - begin & BLOCK_SIZE - 1)
				throwError(Exception(Format("Encryption with PadMode = PAD_MODE_NOPAD requires input size to be multiple of BLOCK_SIZE"))); //63

			out.resize(end - begin, 0); //66

			m_engine.StartEncryption(m_key.data()); //69
			m_engine.Encrypt(begin, out.data(), out.size() >> 4); //70
		}

		else
		{
			int paddingsize = end - begin; //75
			int sizerounded = BLOCK_SIZE - (paddingsize & (BLOCK_SIZE - 1)); //76

			std::vector<unsigned char> inpadded; //79
			inpadded.reserve(sizerounded + paddingsize); //80
			inpadded.assign(begin, end); //81

			if (m_padMode)
			{
				if (m_padMode != PAD_MODE_FIPS81)
				{
					for (int i = 0; i < sizerounded; i++) //87
						inpadded.push_back(sizerounded); //88
				}

				else
				{
					for (int i = 0; i < sizerounded - 1; i++) //93
						inpadded.push_back(rand() - rand() / 0x1000000); //94
					inpadded.push_back(sizerounded); //95
				}
			}

			out.resize(sizerounded + paddingsize, 0); //99

			m_engine.StartEncryption(m_key.data()); //102
			m_engine.Encrypt(inpadded.data(), out.data(), ((sizerounded + paddingsize) >> 4)); //103
		}
	}

	bool decrypt(const unsigned char* begin, const unsigned char* end, std::vector<unsigned char>& out) //107-154 | Correct? Do we use *.data()?
	{
		if (m_padMode == PAD_MODE_NOPAD)
		{
			if (end - begin & (BLOCK_SIZE - 1))
				return false;

			else
			{
				out.resize(end - begin, 0); //117

				if (end - begin)
				{
					m_engine.StartDecryption(m_key.data()); //122 | ?
					m_engine.Decrypt(begin, out.data(), (end - begin >> 4)); //123 | ?
				}

				return true;
			}
		}

		else if (!(end - begin) || (end - begin) & (BLOCK_SIZE - 1))
			return false;

		else
		{
			out.resize(end - begin); //135

			m_engine.StartDecryption(m_key.data()); //138
			m_engine.Decrypt(begin, out.data(), (end - begin >> 4)); //139 | ?

			unsigned char padding = out.back(); //142 back

			if (padding <= BLOCK_SIZE && (out.size() - padding) >= 0)
			{
				out.resize(out.size() - padding, 0); //148
				return true;
			}

			else
				return false;
		}
	}
	
private:
	::AES m_engine; //157
	std::vector<unsigned char> m_key; //158
	PadMode m_padMode; //159
};

AES::AES(const std::vector<unsigned char>& key, KeyLengthBits keyLength, PadMode pad) //162
{
	m_impl = new Impl(key, keyLength, pad); //164
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

void AES::encrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out) //176
{
	if (!in.empty()) //178
		encrypt(in.data(), out.data(), out); //180
}

bool AES::decrypt(const std::vector<unsigned char>& in, std::vector<unsigned char>& out) //183
{
	if (!in.empty()) //185
		return decrypt(in.data(), out.data(), out); //187

	return true;
}

}