#ifndef __EVENT_H__
#define __EVENT_H_



struct Event
{
	enum class EventType
	{
		play,
		pause,
		unpause,
		stop,
		gameobject_destroyed,
		window_resize,
		file_dropped,
		invalid
	} type;

	Event(EventType type) : type(type)
	{}

	const char* string;

	//union
	//{
	//	struct
	//	{
	//		const char* ptr;
	//	} string;

	//	struct
	//	{
	//		int x, y;
	//	} point2d;
	//};


};




#endif // __EVENT_H__