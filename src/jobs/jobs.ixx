module;
#include <infra/Cpp20.h>
#include <infra/Config.h>

export module two.jobs;
import <thread>;
import <mutex>;
import <random>;

export import two.infra;
export import two.type;

#include <jobs/Api.h>

