#ifndef _PF_COMMON_GAMECENTER_H
#define _PF_COMMON_GAMECENTER_H

#include <pf/GameCenter.h>

BEGIN_NAMESPACE(pf)

GameCenter::GameCenter(GameCenterListener listener)
{
	m_impl = new Impl(listener);
}

GameCenter::~GameCenter()
{
}

bool GameCenter::isLocalPlayerAuthenticated() const
{
	return m_impl->isLocalPlayerAuthenticated();
}

GameCenterPlayer GameCenter::getLocalPlayer() const
{
	return m_impl->getLocalPlayer();
}

void GameCenter::showLeaderboard()
{
	m_impl->showLeaderboard();
}

void GameCenter::showAchievements()
{
	m_impl->showAchievements();
}

void GameCenter::postAchievement(const std::string&, float, void*)
{
	//m_impl->postAchievement();
}

void GameCenter::postScore(const std::string&, double, void*)
{
	//m_impl->postScore();
}

void GameCenter::retrieveAchievementProgress()
{
	m_impl->retrieveAchievementProgress();
}

void GameCenter::retrieveAchievementDescriptions(void*)
{
	//m_impl->retrieveAchievementDescriptions();
}

void GameCenter::retrieveFriends(void*)
{
	//m_impl->retrieveAchievementDescriptions();
}

void GameCenter::retrievePlayers(const std::vector<std::string>&, void*)
{
	//m_impl->retrievePlayers();
}

bool GameCenter::isSupported()
{
	return m_impl->isSupported();
}

}

#endif // !_PF_COMMON_GAMECENTER_H