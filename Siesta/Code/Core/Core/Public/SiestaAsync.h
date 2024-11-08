#pragma once

#include "CoreAPI.h"

#include "taskflow/taskflow.hpp"

using TAsyncExecutor = tf::Executor;
using TAsyncGraph = tf::Taskflow;
using TAsyncTask = tf::AsyncTask;

template<typename T>
using TAsyncTaskFuture = tf::Future<T>;