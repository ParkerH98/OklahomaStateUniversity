use F19_phague
go

-- trigger example

drop table HumanLeaseArchive

create table HumanLeaseArchive(

    IrkenName varchar(30) not null,
    VeeblefetzerSerialNumber int not null,
    HumanID int not null,
    LeaseStart date,
    LeaseEnd date,
    AnnualLeaseCost varchar(30)
)

alter table HumanLeaseArchive add constraint HumanLeaseArchivepk primary key (IrkenName, VeeblefetzerSerialNumber, HumanID)


drop trigger ArchiveLeases
go

create trigger ArchiveLeases
on HumanLease
after delete 
as 
    insert into HumanLeaseArchive (IrkenName, VeeblefetzerSerialNumber, HumanID, LeaseStart, LeaseEnd, AnnualLeaseCost)
    select IrkenName, VeeblefetzerSerialNumber, HumanID, LeaseStart, LeaseEnd, AnnualLeaseCost from deleted
go


