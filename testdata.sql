insert into citizen (id, surname, name, patronymic, adress, pass_amount) values (1, 'Котелевский', 'Артём', 'Алексеевич', 'Летняя-39', 0);

insert into сitizen (id, surname, name, patronymic, adress, pass_amount) values (2, 'Котелевский', 'Алексей', 'Алексеевич', 'Летняя-37', 1);

insert into сitizen (id, surname, name, patronymic, adress, pass_amount) values (3, 'Котелевская', 'Маргарита', 'Михайловна', 'Весенняя-5', 2);

insert into type_of_trouble (id, name) values (1, 'Протечка крыши');

insert into type_of_trouble (id, name) values (2, 'Шум во дворе');

insert into type_of_trouble (id, name) values (3, 'Прорыв трубы');

insert into worker (id, surname, name, patronymic, position) values (1, 'Цинпаев', 'Умар', 'Сулейманович', 'Слесарь');

insert into worker (id, surname, name, patronymic, position) values (2, 'Чуев', 'Илья', 'Юрьевич', 'Электрик');

insert into worker (id, surname, name, patronymic, position) values (3, 'Ходос', 'Лев', 'Дмитриевич', 'Сварщик');

insert into status_of_trouble (id, status) values (1, 'Получена');

insert into status_of_trouble (id, status) values (2, 'В проце');

insert into status_of_trouble (id, status) values (3, 'Обработана');
insert into pass_status (id, status) values (7, 'E');

insert into pass_status (id, status) values (10, 'F');

insert into pass_status (id, status) values (11, 'G');

insert into pass (id, car_number, status_id) values (4, '3ААО76', 4);

insert into pass (id, car_number, status_id) values (9, 'D', 6);

insert into pass (id, car_number, status_id) values (14, 'E', 14);

insert into issued_pass (id, pass_id, citizen_id) values (3, 7, 16);

insert into issued_pass (id, pass_id, citizen_id) values (2, 4, 6);

insert into issued_pass (id, pass_id, citizen_id) values (4, 14, 6);

insert into service (id, name) values (1, '5');

insert into service (id, name) values (15, '6');

insert into service (id, name) values (13, '7');

insert into trouble (id, type_id, status_id, worker_id, citizen_id) values (5, 5, 18, 19, 16);

insert into trouble (id, type_id, status_id, worker_id, citizen_id) values (4, 16, 4, 1, 11);

insert into trouble (id, type_id, status_id, worker_id, citizen_id) values (6, 0, 11, 10, 2);

insert into service_workers (id, worker_id, service_id) values (10, 18, 19);

insert into service_workers (id, worker_id, service_id) values (1, 17, 12);

insert into service_workers (id, worker_id, service_id) values (14, 12, 10);