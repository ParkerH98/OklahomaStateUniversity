use F19_phague
go 

-- view example

drop view OpenLeases
go

create view OpenLeases as
select IrkenName, HumanID, LeaseStart from HumanLease
where LeaseEnd > CURRENT_TIMESTAMP
go

select * from OpenLeases    
