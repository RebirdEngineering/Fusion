#ifndef _FUSION_APPRATER_COMMON_APPRATER_H
#define _FUSION_APPRATER_COMMON_APPRATER_H

#include <apprater/common/AppraterImplBase.h>

bool Apprater::check(const Config& config) //11
{
	AppraterImplBase::sm_usedConfig = config; //13
	AppraterImplBase::addTry();
	return AppraterImplBase::needToPrompt();
}

void Apprater::prompt(const std::string& message, //18
	const std::string& yes, //19
	const std::string& no, //20
	const std::string& later, //21
	std::tr1::is_function<void(Result)>& callback, //22
	const std::string& promptReason) //23
{
	AppraterImplBase::sm_callback = callback;
	AppraterImplBase::sm_launchRating = Apprater::Impl::launchRating; //26
	AppraterImplBase::prompt(message, yes, no, later, callback, promptReason);
}