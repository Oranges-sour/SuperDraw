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
	*�߼���ʱ����������
	*@param dt:������һ�θ��µ�ʱ��
	*@return ��
	*/
	void updateSche(float dt);

	/**
	*�߼���ʱ��,ÿһ֡������
	*@param callback:�ص�����
	*@param key:��ֵ
	*@return ��
	*/
	void schedule(const std::function<void(float)>& callback, const std::wstring& key);

	/**
	*�߼���ʱ��
	*@param callback:�ص�����
	*@param interval:���¼��(��
	*@param key:��ֵ
	*@return ��
	*/
	void schedule(const std::function<void(float)>& callback, float interval, const std::wstring& key);

	/**
	*�߼���ʱ��
	*@param callback:�ص�����
	*@param interval:���¼��(��
	*@param repeat:���´���
	*@param delay:��һ�θ��µ��ӳ�ʱ��
	*@param key:��ֵ
	*@return ��
	*/
	void schedule(const std::function<void(float)>& callback, float interval, int repeat, float delay, const std::wstring& key);

	/**
	*�߼���ʱ��,ֻ����һ��
	*@param callback:�ص�����
	*@param delay:��һ�θ��µ��ӳ�ʱ��
	*@param key:��ֵ
	*@return ��
	*/
	void scheduleOnce(const std::function<void(float)>& callback, float delay, const std::wstring& key);

	/**
	*ȡ���߼���ʱ��
	*@param key:��ֵ
	*@return ��
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
