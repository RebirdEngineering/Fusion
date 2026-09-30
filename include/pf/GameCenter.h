#ifndef _PF_GAMECENTER_H
#define _PF_GAMECENTER_H

#include <lang/Object.h>

namespace pf
{

struct GameCenterPlayer //13
{
	std::string identifier; //15
	std::string alias; //16
};

struct GameCenterAchievementDescription //23
{
	std::string identifier; //25
	std::string title; //26
	std::string groupIdentifier; //27
	std::string achievedDescription; //28
	std::string unachievedDescription;//29
	bool hidden; //30
	bool replayable; //31
	int maximumPoints; //32
};

struct GameCenterAchievementProgress //35
{
	std::string identifier; //37
	bool completed; //38
	double percentComplete; //39
};

class GameCenterListener //47
{
public:
	virtual void onAuthenticationStatusChanged(bool); //54

	virtual void onGameCenterModalUIWillBeShown(); //62

	virtual void onGameCenterModalUIWasHidden(); //67

	virtual void onAchievementDescriptionsRetrieved(bool, std::vector<GameCenterAchievementDescription>); //72
	virtual void onAchievementDescriptionsRetrieved(bool, std::vector<GameCenterAchievementDescription>, void*); //73

	virtual void onAchievementProgressRetrieved(bool, std::vector<GameCenterAchievementDescription>); //78
	virtual void onAchievementProgressRetrieved(bool, std::vector<GameCenterAchievementDescription>, void*); //89

	virtual void onFriendsRetrieved(bool, std::vector<GameCenterAchievementDescription>); //84
	virtual void onFriendsRetrieved(bool, std::vector<GameCenterAchievementDescription>, void*); //85

	virtual void onPlayersRetrieved(bool, std::vector<GameCenterAchievementDescription>); //90
	virtual void onPlayersRetrieved(bool, std::vector<GameCenterAchievementDescription>, void*); //91

	virtual void onPostAchievementDone(bool, const std::string&); //96
	virtual void onPostAchievementDone(bool, const std::string&, void*); //97

	virtual void onPostScoreDone(bool, const std::string&, bool); //102
	virtual void onPostScoreDone(bool, const std::string&, bool, void*); //103
};

class GameCenter : //111
	public lang::Object
{
public:
	GameCenter(GameCenterListener* listener); //119 UNOFFICIAL VAR

	~GameCenter(); //124

	bool isLocalPlayerAuthenticated() const; //131

	GameCenterPlayer getLocalPlayer() const; //137

	void showLeaderboard(); //144

	void showAchievements(); //151

	void postAchievement(const std::string&, float, void*); //159

	void postScore(const std::string&, double, void*); //167

	void retrieveAchievementProgress(); //174

	void retrieveAchievementDescriptions(void*); //181

	void retrieveFriends(void*); //188

	void retrievePlayers(const std::vector<std::string>&, void*); //196

	bool isSupported(); //204
private:
	class Impl;
	P(Impl) m_impl; //208 | Impl sizes: [iOS+OSX: 20 bytes]

	GameCenter(const GameCenter&); //210
	GameCenter& operator=(const GameCenter&); //211
};

}

#endif // !_PF_DRMV2_H