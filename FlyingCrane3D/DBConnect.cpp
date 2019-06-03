#include "DBConnect.h"


const uint32_t DBConnect::DEFAULT_PORT = 3306;


DBConnect::DBConnect(CCHARP _server, CCHARP _login,
					 CCHARP _password, CCHARP _database) :
	server(_server), login(_login),
	password(_password), database(_database), port(DEFAULT_PORT) {

	mysql_init(&this->mysql);
	this->connection = mysql_real_connect(&this->mysql,
										  this->server, this->login,
										  this->password, this->database,
										  this->port, 0, 0);
	this->createTablesIfNotExists();
}

DBConnect::~DBConnect() {
	if (this->connection != nullptr) {
		mysql_close(this->connection);
	}
}

int DBConnect::query(const char* q) {
	if (this->connection == nullptr) return 1;

	return mysql_query(this->connection, q);
}

int DBConnect::query(std::string q) {
	return this->query(q.c_str());
}

void DBConnect::createTablesIfNotExists() {
	if (this->connection == nullptr) return;

	std::string req = R"sql(
create table if not exists category (
    id int(11) not null auto_increment,
    name varchar(250) not null default '',
    primary key (id)
);
)sql";

	this->query(req);
}
