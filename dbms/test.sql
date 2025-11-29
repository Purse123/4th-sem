DROP DATABASE IF EXISTS ecommerce;
CREATE DATABASE ecommerce;
USE ecommerce;

CREATE TABLE User (
    UserID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100) NOT NULL,
    Email VARCHAR(100) UNIQUE NOT NULL,
    Phone VARCHAR(20),
    DOB DATE
);

CREATE TABLE Admin (
    AdminID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT NOT NULL,
    PermissionLevel VARCHAR(50),
    FOREIGN KEY (UserID) REFERENCES User(UserID)
);

CREATE TABLE Department (
    DepID INT AUTO_INCREMENT PRIMARY KEY,
    DepName VARCHAR(100) NOT NULL
);

CREATE TABLE Admin_Department (
    AdminID INT,
    DepID INT,
    PRIMARY KEY (AdminID, DepID),
    FOREIGN KEY (AdminID) REFERENCES Admin(AdminID),
    FOREIGN KEY (DepID) REFERENCES Department(DepID)
);

CREATE TABLE Customer (
    CustomerID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT NOT NULL,
    CustomerType VARCHAR(50),
    ShippingAddress VARCHAR(255),
    FOREIGN KEY (UserID) REFERENCES User(UserID)
);

CREATE TABLE Seller (
    SellerID INT AUTO_INCREMENT PRIMARY KEY,
    UserID INT NOT NULL,
    Licence VARCHAR(100),
    CommissionRate DECIMAL(5,2),
    FOREIGN KEY (UserID) REFERENCES User(UserID)
);

CREATE TABLE Product (
    ProductID INT AUTO_INCREMENT PRIMARY KEY,
    SellerID INT NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Category VARCHAR(100),
    Price DECIMAL(10,2) NOT NULL,
    FOREIGN KEY (SellerID) REFERENCES Seller(SellerID)
);

CREATE TABLE Orders (
    OrderID INT AUTO_INCREMENT PRIMARY KEY,
    CustomerID INT NOT NULL,
    Status VARCHAR(50),
    TotalAmount DECIMAL(10,2),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID)
);

CREATE TABLE OrderDetails (
    OrderID INT,
    ProductID INT,
    Quantity INT NOT NULL,
    UnitPrice DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (OrderID, ProductID),
    FOREIGN KEY (OrderID) REFERENCES `Order`(OrderID),
    FOREIGN KEY (ProductID) REFERENCES Product(ProductID)
);

CREATE TABLE Transaction (
    TransactionID INT AUTO_INCREMENT PRIMARY KEY,
    OrderID INT NOT NULL,
    TransactionName VARCHAR(100),
    NetAmount DECIMAL(10,2),
    FOREIGN KEY (OrderID) REFERENCES `Order`(OrderID)
);

CREATE TABLE PaymentMethod (
    PaymentMethodID INT AUTO_INCREMENT PRIMARY KEY,
    MethodName VARCHAR(50) NOT NULL
);

CREATE TABLE TransactionPayment (
    TransactionID INT,
    PaymentMethodID INT,
    PRIMARY KEY (TransactionID, PaymentMethodID),
    FOREIGN KEY (TransactionID) REFERENCES Transaction(TransactionID),
    FOREIGN KEY (PaymentMethodID) REFERENCES PaymentMethod(PaymentMethodID)
);


ALTER USER 'root'@'localhost' IDENTIFIED VIA unix_socket;
FLUSH PRIVILEGES;
