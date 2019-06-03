#pragma once

class DBConnect {
public:
	static const uint32_t DEFAULT_PORT;

protected:
	MYSQL* connection;
	MYSQL mysql;

protected:
	std::string server;
	std::string login;
	std::string password;
	std::string database;
	uint32_t port;

protected:
	bool isConnectionError();
	void createTablesIfNotExists();

public:
	DBConnect() = delete;
	DBConnect(std::string _server,
			  std::string _login,
			  std::string _password,
			  std::string _database);
	virtual ~DBConnect();

	int query(const char* q);
	int query(std::string q);
};
