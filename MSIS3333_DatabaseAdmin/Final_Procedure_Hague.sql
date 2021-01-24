use F19_phague
go 

-- procedure example

drop procedure TineCheck
go

create procedure TineCheck
@IntegerBeingPassed int
as 

declare @HumanID int 
declare @FirstName varchar(30)
declare @LastName varchar(30)
declare @Tines int

declare pcursor cursor
for 
select distinct Human.HumanID, FirstName, LastName, Tines
from Human
join UtensilOwnership on UtensilOwnership.HumanID = Human.HumanID
join Utensil on Utensil.LatinCodeword = UtensilOwnership.LatinCodeword
join Spork on Spork.SLatinCodeword = Utensil.LatinCodeword


open pcursor 
fetch next from pcursor into @HumanID, @FirstName, @LastName, @Tines

drop table TinyTines

create table TinyTines(
    TinesID int identity(1, 1) primary key,
    HumanID int,
    FirstName varchar(30),
    LastName varchar(30),
    Tines int
)

while @@FETCH_STATUS = 0

begin 

if @Tines <= @IntegerBeingPassed
insert into TinyTines values (@HumanID, @FirstName, @LastName, @Tines)

fetch next from pcursor into @HumanID, @FirstName, @LastName, @Tines

end 

close pcursor
deallocate pcursor

go

exec TineCheck 3

select * from TinyTines
