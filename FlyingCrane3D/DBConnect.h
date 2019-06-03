#pragma once

class DBConnect {
protected:
	using CCHARP = const char*;

public:
	static const uint32_t DEFAULT_PORT;

protected:
	MYSQL* connection;
	MYSQL mysql;

protected:
	CCHARP server;
	CCHARP login;
	CCHARP password;
	CCHARP database;
	uint32_t port;

protected:
	void createTablesIfNotExists();

public:
	DBConnect() = delete;
	DBConnect(CCHARP _server,
			  CCHARP _login,
			  CCHARP _password,
			  CCHARP _database);
	virtual ~DBConnect();

	int query(const char* q);
	int query(std::string q);
};
