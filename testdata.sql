insert into citizen (id, surname, name, patronymic, adress, pass_amount) values (1, '�����������', '����', '����������', '������-39', 0);

insert into �itizen (id, surname, name, patronymic, adress, pass_amount) values (2, '�����������', '�������', '����������', '������-37', 1);

insert into �itizen (id, surname, name, patronymic, adress, pass_amount) values (3, '�����������', '���������', '����������', '��������-5', 2);

insert into type_of_trouble (id, name) values (1, '�������� �����');

insert into type_of_trouble (id, name) values (2, '��� �� �����');

insert into type_of_trouble (id, name) values (3, '������ �����');

insert into worker (id, surname, name, patronymic, position) values (1, '�������', '����', '������������', '�������');

insert into worker (id, surname, name, patronymic, position) values (2, '����', '����', '�������', '��������');

insert into worker (id, surname, name, patronymic, position) values (3, '�����', '���', '����������', '�������');

insert into status_of_trouble (id, status) values (1, '��������');

insert into status_of_trouble (id, status) values (2, '� �����');

insert into status_of_trouble (id, status) values (3, '����������');
insert into pass_status (id, status) values (7, 'E');

insert into pass_status (id, status) values (10, 'F');

insert into pass_status (id, status) values (11, 'G');

insert into pass (id, car_number, status_id) values (4, '3���76', 4);

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