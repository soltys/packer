#pragma once
#include "PackSink.h"

namespace packer
{
	class SqlitePackSink : public packer::PackSink
	{
	public:
		void Initialize(packer::PackerArgument packer_argument) override;
	};
}