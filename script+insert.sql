create table citizen (
id integer not null,
surname varchar(20) not null,
name varchar(20) not null,
patronymic varchar(20) not null,
adress varchar(20) not null,
pass_amount integer,
trouble_amount integer,
primary key (id)
);

create table status_of_trouble (
id integer not null,
status varchar(20) not null,
primary key (id)
);

create table type_of_trouble (
id integer not null,
name varchar(20),
trouble_amount integer,
primary key (id)
);

create table worker (
id integer not null,
surname varchar(20) not null,
name varchar(20) not null,
patronymic varchar(20) not null,
position varchar(20) not null,
primary key (id)
);

create table archivated_trouble (
id integer not null,
type_id integer not null,
status_id integer not null,
worker_id integer not null,
citizen_id integer not null,
date_of_resolving datetime,
foreign key (type_id)
      references type_of_trouble (id),
foreign key (status_id)
      references status_of_trouble (id),
foreign key (worker_id)
      references worker (id),
foreign key (citizen_id)
      references citizen (id),
);

create table pass_status (
id integer not null,
status varchar(20) not null,
primary key (id)
);

create table pass (
id integer not null,
car_number varchar(20),
pass_status_id int,
time_of_issue datetime,
primary key (id),
foreign key (pass_status_id)
      references pass_status (id)
);

create table issued_pass (
id integer not null,
pass_id integer,
citizen_id integer,
primary key (id),
foreign key (pass_id)
      references pass (id),
foreign key (citizen_id)
      references citizen (id)
);

create table service (
id integer not null,
name varchar(20) not null,
primary key (id)
);

create table service_workers (
id integer not null,
worker_id integer,
service_id integer,
primary key (id),
foreign key (worker_id)
      references worker (id),
foreign key (service_id)
      references service (id)
);

create table trouble (
id integer not null,
type_id integer not null,
status_id integer not null,
worker_id integer not null,
citizen_id integer not null,
creation_date datetime,
primary key (id),
foreign key (type_id)
      references type_of_trouble (id),
foreign key (status_id)
      references status_of_trouble (id),
foreign key (worker_id)
      references worker (id),
foreign key (citizen_id)
      references citizen (id)
);

insert into status_of_trouble(id, status) values(1,'Получена')
insert into status_of_trouble(id, status) values(2,'На рассмотрении')
insert into status_of_trouble(id, status) values(3,'На исполнении')
insert into status_of_trouble(id, status) values(4,'Исполнена')
insert into type_of_trouble(id, name, trouble_amount) values (1, 'Отсутствие света',0)
insert into type_of_trouble(id, name, trouble_amount) values (2, 'Разрыв метал трубы',0)
insert into type_of_trouble(id, name, trouble_amount) values (3, 'Шум во дворе',0)
insert into pass_status(id, status) values (1, 'Активен')
insert into pass_status(id, status) values (2, 'Неактивен')
insert into сitizen(id, surname, name, patronymic, adress,pass_amount,trouble_amount ) values (1, 'Котелевский', 'Артём', 'Алексеевич', 'Летняя 39',0,0)
insert into citizen(id, surname, name, patronymic, adress, pass_amount,trouble_amount ) values (2, 'Котелевский', 'Алексей', 'Алексеевич', 'Летняя-37', 1,0);
insert into citizen(id, surname, name, patronymic, adress, pass_amount,trouble_amount ) values (3, 'Котелевская', 'Маргарита', 'Михайловна', 'Весенняя-5', 2,0);
insert into citizen(id, surname, name, patronymic, adress, pass_amount,trouble_amount ) values (4, 'Чуевштейн', 'Илья', 'Юрьевич', 'Весенняя-49', 0,0);
insert into citizen(id, surname, name, patronymic, adress, pass_amount,trouble_amount ) values (5, 'Андропов', 'Кирилл', 'Сергеевич', 'Осенняя-13', 0,0);
insert into worker (id, surname, name, patronymic, position) values (1, 'Цинпаев', 'Умар', 'Сулейманович', 'Слесарь');
insert into worker (id, surname, name, patronymic, position) values (2, 'Чуев', 'Илья', 'Юрьевич', 'Электрик');
insert into worker (id, surname, name, patronymic, position) values (3, 'Ходос', 'Лев', 'Дмитриевич', 'Сварщик');
insert into trouble(id, type_id, status_id, worker_id, citizen_id) values (1, 1, 1, 2, 2);
insert into pass(id, car_number) values (3, 'П863КК')
insert into pass(id, car_number) values (1, 'А739ФК')
insert into pass(id, car_number) values (2, 'М373УФ')
insert into pass(id, car_number) values (4, 'Л111ЦМ')
insert into pass(id, car_number) values (5, 'С777ЩУ')
insert into service(id, name) values (1, 'Водоканал')
insert into service(id, name) values (2, 'Энерго')
insert into service(id, name) values (3, 'Звезда')
insert into trouble(id, type_id, status_id, worker_id, citizen_id) values (3, 2, 1, 3, 3);
insert into service_workers(id, worker_id, service_id) values (1, 1, 1)
insert into service_workers(id, worker_id, service_id) values (2, 2, 2)
insert into service_workers(id, worker_id, service_id) values (3, 3, 3)
