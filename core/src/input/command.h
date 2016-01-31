#pragma once

namespace core {
	class Command {
	public:
		virtual ~Command() {}
		virtual void execute() = 0;
	};
}