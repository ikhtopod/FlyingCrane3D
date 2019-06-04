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

	std::string createTableCategories = R"sql(
create table if not exists categories (
    id int(11) not null auto_increment,
    name varchar(250) not null unique,
    primary key (id)
);
)sql";

	std::string createTableScenes = R"sql(
create table if not exists scenes (
    id int(11) not null,
    name varchar(250) not null unique,
	category_id int(11) not null,
    primary key (id)
);
)sql";

	std::string createTableObjects = R"sql(
create table if not exists objects (
    id int(11) not null,
    name varchar(250) not null,
	scene_id int(11) not null,
    primary key (id),
	foreign key (scene_id) references scenes (id)
		on delete cascade
		on update cascade
);
)sql";

	std::string createTableTransforms = R"sql(
create table if not exists transforms (
    id int(11) not null,
	position varchar(80) not null default '0.0;0.0;0.0',
	rotation varchar(80) not null default '0.0;0.0;0.0',
	scale varchar(80) not null default '1.0;1.0;1.0',
    primary key (id),
	foreign key (id) references objects (id)
		on delete cascade
		on update cascade
);
)sql";

	std::string createTableMeshes = R"sql(
create table if not exists meshes (
    id int(11) not null,
    name varchar(250) not null,
	`object_id` int(11) not null,
    primary key (id),
	foreign key (`object_id`) references objects (id)
		on delete cascade
		on update cascade
);
)sql";

	std::string createTablePolymeshes = R"sql(
create table if not exists polymeshes (
    id int(11) not null,
    `index` int(11) not null,
	vertex varchar(80) not null default '0.0;0.0;0.0',
	foreign key (id) references meshes (id)
		on delete cascade
		on update cascade
);
)sql";

	this->query(createTableCategories);
	this->query(createTableScenes);
	this->query(createTableObjects);
	this->query(createTableTransforms);
	this->query(createTableMeshes);
	this->query(createTablePolymeshes);
}
