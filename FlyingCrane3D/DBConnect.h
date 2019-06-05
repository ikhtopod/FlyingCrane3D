#pragma once

class DBConnect {
public:
	static const uint32_t DEFAULT_PORT;

protected:
	static std::string vectorToString(const glm::vec3& vctr);
	static glm::vec3 stringToVector(const std::string& vctr);

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
	int query(const std::string& q);

	uint32_t getCategoryIdByName(std::string categoryName);
	std::vector<const char *> getColumnContent(std::string tableName, std::string colName);
	std::vector<const char *> getColumnContentByCategory(std::string tableName,
														 std::string colName,
														 std::string category);
	uint32_t getFreeRow(std::string tableName, std::string colIdName);
};
