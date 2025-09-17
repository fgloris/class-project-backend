#pragma once

#include <cstddef>
#include <string>
#include <chrono>

namespace config {

struct ConnectionPoolConfig{
  size_t min_connections;
  size_t max_connections;
  std::chrono::milliseconds timeout;
  std::chrono::seconds idle_timeout;
};

struct DatabaseConfig {
  std::string host;
  unsigned int port;
  std::string user;
  std::string password;
  std::string db_name;
  std::string charset;
};

struct RedisConfig {
  std::string host;
  unsigned int port;
};

struct GrpcServiceConfig {
  std::string host;
  int port;
};

struct StreamingConfig {
  std::string host;
  int port;
};

struct AuthConfig {
  std::string jwt_secret;
  int jwt_expire_hours;
};

struct SMTPConfig {
  std::string server;
  int port;
  std::string password;
  std::string from_email;
  std::string email_sender_name;
  size_t queue_max_size;
};

class Config {
public:
static Config& getInstance() {
  static Config instance;
  return instance;
}

// Delete copy/move constructors and assign operators
Config(const Config&) = delete;
Config& operator=(const Config&) = delete;
Config(Config&&) = delete;
Config& operator=(Config&&) = delete;

// Getters
const DatabaseConfig& getDatabase() const { return database_; }
const RedisConfig& getRedis() const { return redis_ ;}
const GrpcServiceConfig& getUserService() const { return user_service_; }
const StreamingConfig& getStreaming() const { return streaming_; }
const AuthConfig& getAuth() const { return auth_; }
const SMTPConfig& getSMTP() const { return smtp_; }
const ConnectionPoolConfig& getDBCntPool() const { return db_cp_; }
const ConnectionPoolConfig& getSMTPCntPool() const { return db_cp_; }
std::string getUserServiceIpPort() const { return user_service_.host+":"+std::to_string(user_service_.port);}

private:
  Config();

  RedisConfig redis_;
  DatabaseConfig database_;
  GrpcServiceConfig user_service_;
  StreamingConfig streaming_;
  AuthConfig auth_;
  SMTPConfig smtp_;
  ConnectionPoolConfig db_cp_;
  ConnectionPoolConfig smtp_cp_;
};

} // namespace config
