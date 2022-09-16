#include <catch2/catch_test_macros.hpp>

#include <spdlog/spdlog.h>

namespace libvk
{
	class child
	{
	public:
		child()
		{
			SPDLOG_TRACE("");
		}

		~child()
		{
			SPDLOG_TRACE("");
		}
	};

	class parent
	{
		child child00_{};
		child child01_{};
		child child02_{};

	public:
		parent()
		{
			SPDLOG_TRACE("");
		}

		~parent()
		{
			SPDLOG_TRACE("");
		}
	};
}

TEST_CASE("constructor & desctructor order", "[constructor_destructor_order]")
{
	spdlog::set_pattern("[%H:%M:%S.%e] [%^%L%$] [thread:%t] [%!:%#] %v");
	spdlog::set_level(spdlog::level::trace);

	auto parent = libvk::parent();
}

/**
 * \brief RESULTS

[12:38:48.322] [T] [thread:13624] [libvk::child::child:12]
[12:38:48.322] [T] [thread:13624] [libvk::child::child:12]
[12:38:48.322] [T] [thread:13624] [libvk::child::child:12]
[12:38:48.323] [T] [thread:13624] [libvk::parent::parent:30]
[12:38:48.323] [T] [thread:13624] [libvk::parent::~parent:35]
[12:38:48.323] [T] [thread:13624] [libvk::child::~child:17]
[12:38:48.324] [T] [thread:13624] [libvk::child::~child:17]
[12:38:48.324] [T] [thread:13624] [libvk::child::~child:17]

This shows that the parent destructor is called first and then the child destructors are called.

 */
