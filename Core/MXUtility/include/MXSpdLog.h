//
// Created by brillan on 2023/11/18.
//


#ifndef MYSPDLOG_H
#define MYSPDLOG_H

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/stopwatch.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/callback_sink.h"
#include <iostream>
#include <GlobalDef.h>

MX_API void initSpdLog(std::string log_path);

MX_API std::shared_ptr<spdlog::logger> get_async_file_logger(std::string name);

#define INITLOG()     init_spdlog()


#define TRACE(...)     SPDLOG_TRACE(__VA_ARGS__)
#define DEBUG(...)     SPDLOG_DEBUG(__VA_ARGS__)
#define INFO(...)      SPDLOG_INFO(__VA_ARGS__)
#define WARN(...)      SPDLOG_WARN(__VA_ARGS__)
#define ERROR(...)     SPDLOG_ERROR(__VA_ARGS__)
#define CRITICAL(...)  SPDLOG_CRITICAL(__VA_ARGS__)

//单个日志文件
#define GETLOG(LOG_NAME) get_async_file_logger(LOG_NAME)

#define LOGGER_TRACE(logger, ...)     SPDLOG_LOGGER_TRACE(logger,__VA_ARGS__)
#define LOGGER_DEBUG(logger, ...)     SPDLOG_LOGGER_DEBUG(logger,__VA_ARGS__)
#define LOGGER_INFO(logger, ...)      SPDLOG_LOGGER_INFO(logger,__VA_ARGS__)
#define LOGGER_WARN(logger, ...)      SPDLOG_LOGGER_WARN(logger,__VA_ARGS__)
#define LOGGER_ERROR(logger, ...)     SPDLOG_LOGGER_ERROR(logger,__VA_ARGS__)
#define LOGGER_CRITICAL(logger, ...)  SPDLOG_LOGGER_CRITICAL(logger,__VA_ARGS__)

//时间统计宏
#define LOGSW() spdlog::stopwatch()


class MX_API LogRunTime
{
public:
	explicit LogRunTime(std::string name);
	~LogRunTime();

private:
	std::string m_name;
	spdlog::stopwatch m_sw;
};


#define LOG_RUN_TIME(name) LogRunTime log_run_time(name)


#endif //MYSPDLOG_H
