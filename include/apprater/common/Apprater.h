#ifndef _FUSION_APPRATER_COMMON_APPRATER_H
#define _FUSION_APPRATER_COMMON_APPRATER_H

#include <apprater/common/AppraterImplBase.h>

bool Apprater::check(const Config& config)
{
	AppraterImplBase::sm_usedConfig.iTunesAppId = config.iTunesAppId;
	AppraterImplBase::sm_usedConfig.daysUntilPromptFirst = config.daysUntilPromptFirst;
	AppraterImplBase::sm_usedConfig.daysUntilPromptLater = config.daysUntilPromptLater;
	AppraterImplBase::sm_usedConfig.triesUntilPromptFirst = config.triesUntilPromptFirst;
	AppraterImplBase::addTry();
	return AppraterImplBase::needToPrompt();
}

void Apprater::prompt(const std::string& message, const std::string& yes, const std::string& no, const std::string& later, std::tr1::is_function<void(Result)>& callback, const std::string& promptReason)
{
	AppraterImplBase::sm_launchRating = Apprater::Impl::launchRating;
	AppraterImplBase::prompt(message, yes, no, later, callback, promptReason);
}