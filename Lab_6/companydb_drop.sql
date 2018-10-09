alter table employee drop FOREIGN KEY fk_super_ssn;
alter table department drop FOREIGN KEY fk_mgr_ssn;
alter table works_on drop FOREIGN KEY fk_essn;  
alter table dependent drop FOREIGN KEY fk_dessn;
drop table employee;
