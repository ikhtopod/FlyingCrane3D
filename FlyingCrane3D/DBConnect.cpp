#include "DBConnect.h"


const uint32_t DBConnect::DEFAULT_PORT = 3306;


DBConnect::DBConnect(std::string _server, std::string _login,
					 std::string _password, std::string _database) :
	server(_server), login(_login),
	password(_password), database(_database), port(DEFAULT_PORT) {

	mysql_init(&this->mysql);
	this->connection = mysql_real_connect(&this->mysql,
										  this->server.c_str(), this->login.c_str(),
										  this->password.c_str(), this->database.c_str(),
										  this->port, 0, 0);



	this->createTablesIfNotExists();
}

DBConnect::~DBConnect() {
	if (this->connection != nullptr) {
		mysql_close(this->connection);
	}
}

int DBConnect::query(const char* q) {
	if (this->isConnectionError()) return 1;

	return mysql_query(this->connection, q);
}

int DBConnect::query(std::string q) {
	return this->query(q.c_str());
}

bool DBConnect::isConnectionError() {
	if (this->connection == nullptr) {
		std::cout << mysql_error(&this->mysql) << std::endl;
		return true;
	}

	return false;
}

void DBConnect::createTablesIfNotExists() {
	if (this->isConnectionError()) return;

	std::string req = R"sql(
create table if not exists category (
    id int(11) not null auto_increment,
    name varchar(250) not null default '',
    primary key (id)
);
)sql";

	this->query(req);
}
