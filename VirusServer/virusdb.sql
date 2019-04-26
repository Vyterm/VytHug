drop database if exists `virus_db`;
create database `virus_db`;
use `virus_db`;

create table `md5_virus_table`(
	`virus_id` int not null auto_increment,
	`virus_tag` varchar(50) not null unique,
    `virus_name` varchar(50) not null default 'Trojan',
    primary key(virus_id)
);

insert into `md5_virus_table`(`virus_tag`) values (MD5('1JXahbu230x1Zehim88t'));
select `virus_tag` from `md5_virus_table`;
delete from `md5_virus_table` where `virus_tag` = MD5('1JXahbu230x1Zehim88t');
select `virus_tag` from `md5_virus_table`;

select * from `md5_virus_table`;