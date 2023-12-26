#ifndef _NONCOPYABLE_HPP_
#define _NONCOPYABLE_HPP_

class NonCopyable {
public:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

protected:
	NonCopyable() = default;
	~NonCopyable() = default;
};

#endif // _NONCOPYABLE_HPP_
