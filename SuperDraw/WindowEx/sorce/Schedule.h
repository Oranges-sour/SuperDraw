//
//  Schedule.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include <functional>
#include <map>
#include <string>


class Schedule
{
public:
	/**
	*逻辑定时器的主更新
	*@param dt:距离上一次更新的时间
	*@return 无
	*/
	void updateSche(float dt);

	/**
	*逻辑定时器,每一帧都更新
	*@param callback:回调函数
	*@param key:键值
	*@return 无
	*/
	void schedule(const std::function<void(float)>& callback, const std::wstring& key);

	/**
	*逻辑定时器
	*@param callback:回调函数
	*@param interval:更新间隔(秒
	*@param key:键值
	*@return 无
	*/
	void schedule(const std::function<void(float)>& callback, float interval, const std::wstring& key);

	/**
	*逻辑定时器
	*@param callback:回调函数
	*@param interval:更新间隔(秒
	*@param repeat:更新次数
	*@param delay:第一次更新的延迟时间
	*@param key:键值
	*@return 无
	*/
	void schedule(const std::function<void(float)>& callback, float interval, int repeat, float delay, const std::wstring& key);

	/**
	*逻辑定时器,只更新一次
	*@param callback:回调函数
	*@param delay:第一次更新的延迟时间
	*@param key:键值
	*@return 无
	*/
	void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::wstring& key);

	/**
	*取消逻辑定时器
	*@param key:键值
	*@return 无
	*/
	void unschedule(const std::wstring& key);
private:
	struct SchedulePack
	{
		std::function<void(float)> callBack;
		int repeat;
		float delay;
		float interval;
		float timeCount;
	};

	std::map<std::wstring, SchedulePack> scheduleMap;
};

#endif
