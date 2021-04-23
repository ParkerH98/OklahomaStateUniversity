
--This
--begins
--the
--stored
--procedure
--scripts
USE [F20_ksphague]
GO

/****** Object:  StoredProcedure [dbo].[spInsertCredentials]    Script Date: 12/7/2020 7:20:30 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



create procedure [dbo].[spInsertCredentials]
@FirstName varchar(25),
@LastName varchar(25),
@PrimaryAddress varchar(100),
@SecondaryAddress varchar(100),
@City varchar(50),
@StateID int,
@Zipcode varchar(5),
@PhoneNumber char(14),
@Username varchar(50),
@UserPassword varchar(100),
@RecoveryEmail varchar(50)


as
begin
	insert into UserAccount (
	FirstName,
	LastName,
	PrimaryAddress,
	SecondaryAddress,
	City,
	StateID,
	Zipcode,
	UserName,
	UserPassword,
	RecoveryEmail,
	PhoneNumber
	)
	values (
	@FirstName,
	@LastName,
	@PrimaryAddress,
	@SecondaryAddress,
	@City,
	@StateID,
	@Zipcode,
	@UserName,
	@UserPassword,
	@RecoveryEmail,
	@PhoneNumber
	)

end
 
GO

/****** Object:  StoredProcedure [dbo].[spInsertMyOrder]    Script Date: 12/7/2020 7:20:31 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO




create procedure [dbo].[spInsertMyOrder]
@AccountNumber int,
@CustomerFirstName varchar(25),
@CustomerLastName varchar(25),
@PrimaryShippingAddress varchar(100),
@SecondaryShippingAddress varchar(100),
@ShippingState int,
@ShippingCity varchar(50),
@ShippingZip varchar(5),
@OrderNumber int output,
@OrderItems OrderItemsTableType READONLY
as

begin

insert into OrderHeader(AccountNumber, CustomerFirstName, CustomerLastName, PrimaryShippingAddress, SecondaryShippingAddress, ShippingState, ShippingCity, ShippingZip, OrderDate)
values
(@AccountNumber, @CustomerFirstName, @CustomerLastName, @PrimaryShippingAddress, @SecondaryShippingAddress, @ShippingState, @ShippingCity, @ShippingZip, GETDATE());
	
	set @OrderNumber = SCOPE_IDENTITY();



	insert into OrderDetail
	(OrderHeaderID, ProductID, QuantityOrdered, UnitPrice)
	select @OrderNumber, ProductID, Quantity, UnitPrice from @OrderItems
	

end

GO

/****** Object:  StoredProcedure [dbo].[spSelectAllStates]    Script Date: 12/7/2020 7:20:31 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO



create procedure [dbo].[spSelectAllStates]
as
begin
	Select StateID, StateName, StateAbbr
	from State
	order by StateAbbr
	
end
GO

/****** Object:  StoredProcedure [dbo].[spSelectProductByID]    Script Date: 12/7/2020 7:20:31 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO






create procedure [dbo].[spSelectProductByID]
@ProductID int
as
begin

	select ProductID, ProductName, UnitPrice, ShortDesc, LongDesc, ProductAvailability, ProductInventoryQuantity, ProductCategory from Product
	where ProductID = @ProductID
	order by ProductName

end
GO

/****** Object:  StoredProcedure [dbo].[spSelectUserByCredentials]    Script Date: 12/7/2020 7:20:32 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO




create procedure [dbo].[spSelectUserByCredentials]
@Username varchar(100), 
@UserPassword varchar(50)
as
begin
	Select UserID, FirstName, LastName, PrimaryAddress, SecondaryAddress, City, StateID, Zipcode,
		   UserName, UserPassword, RecoveryEmail, PhoneNumber
	from UserAccount
	where UserName = @Username and
		  UserPassword = @UserPassword
end
GO

/****** Object:  StoredProcedure [dbo].[spUpdateAccount]    Script Date: 12/7/2020 7:20:32 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO






create procedure [dbo].[spUpdateAccount]
@FirstName varchar(25),
@LastName varchar(25),
@PrimaryAddress varchar(100),
@SecondaryAddress varchar(100),
@City varchar(50),
@StateID int,
@Zipcode varchar(5),
@PhoneNumber char(14),
@Username varchar(50),
@UserPassword varchar(100)



as
begin

update UserAccount

set FirstName = @FirstName,
	LastName = @LastName,
	PrimaryAddress = @PrimaryAddress,
	SecondaryAddress = @SecondaryAddress,
	City = @City,
	StateID  = @StateID,
	UserPassword = @UserPassword,
	PhoneNumber = @PhoneNumber



where Username = @Username


end
 
GO
--This
--ends
--the
--stored
--procedure
--scripts


--This
--begins
--the
--tables
--scripts
CREATE TABLE [dbo].[OrderDetail](
	[OrderDetailID] [int] IDENTITY(1,1) NOT NULL,
	[OrderHeaderID] [int] NOT NULL,
	[ProductID] [int] NOT NULL,
	[UnitPrice] [decimal](18, 2) NOT NULL,
	[QuantityOrdered] [int] NOT NULL,
	[paymentType] [varchar](25) NULL,
PRIMARY KEY CLUSTERED 
(
	[OrderDetailID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

/****** Object:  Table [dbo].[OrderHeader]    Script Date: 12/7/2020 7:21:51 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[OrderHeader](
	[OrderNumber] [int] IDENTITY(1,1) NOT NULL,
	[AccountNumber] [int] NOT NULL,
	[OrderDate] [datetime] NOT NULL,
	[CustomerFirstName] [varchar](25) NOT NULL,
	[CustomerLastName] [varchar](25) NOT NULL,
	[PrimaryShippingAddress] [varchar](100) NOT NULL,
	[SecondaryShippingAddress] [varchar](100) NULL,
	[ShippingState] [int] NOT NULL,
	[ShippingCity] [varchar](50) NOT NULL,
	[ShippingZip] [varchar](5) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[OrderNumber] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

/****** Object:  Table [dbo].[Product]    Script Date: 12/7/2020 7:21:51 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Product](
	[ProductID] [int] IDENTITY(1,1) NOT NULL,
	[ProductName] [varchar](100) NULL,
	[UnitPrice] [decimal](18, 2) NOT NULL,
	[ShortDesc] [varchar](500) NOT NULL,
	[LongDesc] [varchar](1000) NULL,
	[ProductAvailability] [bit] NOT NULL,
	[ProductInventoryQuantity] [int] NOT NULL,
	[ProductCategory] [varchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[ProductID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

/****** Object:  Table [dbo].[State]    Script Date: 12/7/2020 7:21:51 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[State](
	[StateID] [int] IDENTITY(1,1) NOT NULL,
	[StateName] [varchar](50) NOT NULL,
	[StateAbbr] [char](2) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[StateID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

/****** Object:  Table [dbo].[UserAccount]    Script Date: 12/7/2020 7:21:51 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[UserAccount](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[FirstName] [varchar](25) NOT NULL,
	[LastName] [varchar](25) NOT NULL,
	[PrimaryAddress] [varchar](100) NOT NULL,
	[SecondaryAddress] [varchar](100) NULL,
	[City] [varchar](50) NOT NULL,
	[StateID] [int] NOT NULL,
	[Zipcode] [varchar](5) NOT NULL,
	[PhoneNumber] [varchar](14) NOT NULL,
	[Username] [varchar](50) NOT NULL,
	[UserPassword] [varchar](100) NOT NULL,
	[RecoveryEmail] [varchar](50) NOT NULL,
PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY],
 CONSTRAINT [UQ_Username] UNIQUE NONCLUSTERED 
(
	[Username] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[OrderDetail]  WITH CHECK ADD FOREIGN KEY([OrderHeaderID])
REFERENCES [dbo].[OrderHeader] ([OrderNumber])
GO

ALTER TABLE [dbo].[OrderDetail]  WITH CHECK ADD FOREIGN KEY([ProductID])
REFERENCES [dbo].[Product] ([ProductID])
GO

ALTER TABLE [dbo].[OrderHeader]  WITH CHECK ADD FOREIGN KEY([AccountNumber])
REFERENCES [dbo].[UserAccount] ([UserID])
GO

ALTER TABLE [dbo].[UserAccount]  WITH CHECK ADD FOREIGN KEY([StateID])
REFERENCES [dbo].[State] ([StateID])
GO
--This
--ends
--the
--tables
--scripts