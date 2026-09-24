#ifndef _PF_GAMECENTER_H
#define _PF_GAMECENTER_H

#include <lang/Object.h>

BEGIN_NAMESPACE(pf)

struct GameCenterPlayer
{
public:
	std::string identifier;
	std::string alias;
};

struct GameCenterAchievementDescription
{
public:
	std::string identifier;
	std::string title;
	std::string groupIdentifier;
	std::string achievedDescription;
	std::string unachievedDescription;
	bool hidden;
	bool replayable;
	int maximumPoints;
};

struct GameCenterAchievementProgress
{
public:
	std::string identifier;
	bool completed;
	double percentComplete;
};

class GameCenterListener
{
public:
	virtual void onAuthenticationStatusChanged(bool);

	virtual void onGameCenterModalUIWillBeShown();

	virtual void onGameCenterModalUIWasHidden();

	virtual void onAchievementDescriptionsRetrieved(bool, const std::vector<GameCenterAchievementDescription>);
	virtual void onAchievementDescriptionsRetrieved(bool, const std::vector<GameCenterAchievementDescription>, void*);

	virtual void onAchievementProgressRetrieved(bool, const std::vector<GameCenterAchievementDescription>);
	virtual void onAchievementProgressRetrieved(bool, const std::vector<GameCenterAchievementDescription>, void*);

	virtual void onFriendsRetrieved(bool, const std::vector<GameCenterAchievementDescription>);
	virtual void onFriendsRetrieved(bool, const std::vector<GameCenterAchievementDescription>, void*);

	virtual void onPlayersRetrieved(bool, const std::vector<GameCenterAchievementDescription>);
	virtual void onPlayersRetrieved(bool, const std::vector<GameCenterAchievementDescription>, void*);

	virtual void onPostAchievementDone(bool, const std::string&);
	virtual void onPostAchievementDone(bool, const std::string&, void*);

	virtual void onPostScoreDone(bool, const std::string&, bool);
	virtual void onPostScoreDone(bool, const std::string&, bool, void*);
};

class GameCenter :
	public Object
{
public:
	GameCenter(GameCenterListener listener); //UNOFFICIAL VAR

	~GameCenter();

	bool isLocalPlayerAuthenticated() const;

	GameCenterPlayer getLocalPlayer() const;

	void showLeaderboard();

	void showAchievements();

	void postAchievement(const std::string&, float, void*);

	void postScore(const std::string&, double, void*);

	void retrieveAchievementProgress();

	void retrieveAchievementDescriptions(void*);

	void retrieveFriends(void*);

	void retrievePlayers(const std::vector<std::string>&, void*);

	bool isSupported();
private:
	class Impl;
	P(Impl) m_impl;

	GameCenter(const GameCenter&);
	GameCenter& operator=(const GameCenter&);
};

}

#endif // !_PF_DRMV2_H