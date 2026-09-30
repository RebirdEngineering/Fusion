#include <pf/GameCenter.h>

using namespace lang;

namespace pf
{
	class GameCenter::Impl : public Object //No RTTI on Win32 and WP8?
	{
	public:
		Impl(GameCenterListener* listener)
		{
		}

		~Impl()
		{
		}

		bool isLocalPlayerAuthenticated() const
		{
			return false;
		}

		GameCenterPlayer getLocalPlayer() const;

		void showLeaderboard();

		void showAchievements();

		void postAchievement(const std::string&, float, void*);

		void postScore(const std::string&, double, void*);

		void retrieveAchievementProgress();

		void retrieveAchievementDescriptions(void*);

		void retrieveFriends(void*);

		void retrievePlayers(const std::vector<std::string>&, void*);

		bool isSupported()
		{
			return false;
		}

	private: //Assumptions via iOS
		GameCenterListener* m_listener;
		std::string m_localPlayerID;

		static bool sm_isSupported;
	};

#include <pf/common/GameCenter.h>

}