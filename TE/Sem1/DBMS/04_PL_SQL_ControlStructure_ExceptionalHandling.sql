-- Unnamed PL/SQL code block: Use of Control structure and Exception handling is mandatory.
-- Write a PL/SQL block of code for the following requirements:-
-- Schema:
-- 1. Borrower(Roll, Name, DateofIssue, NameofBook, Status)
-- 2. Fine (Roll, Date, Amt)
-- Accept Roll & N ame of book from user.
-- Check the number of days (from date of issue), if days are between 15 to 30 then fine amount will be Rs 5per day.
-- If no. of days>30, per day fine will be Rs 50 per day & for days less than 30, Rs. 5 per day.
-- After submitting the book, status will change from I to R.
-- If condition of fine is true, then details will be stored into fine table.
-- Frame the problem statement for writing PL/SQL block inline with above statement.

  
  create table Borrower
 ( Roll_no int primary key,
 Name varchar(255),
 DateOfIssue date,
 NameOfBook varchar(255),
 Status varchar(45)
 );
 
 CREATE TABLE Fine(
    Roll_no int,
    Date date,
    Amt int
);

select * from Fine;

INSERT INTO Borrower (Roll_no, Name, DateOfIssue, NameOfBook, Status) 
VALUES
    (1, 'Amita', '2017-06-25', 'Java', 'I'),
    (2, 'Sonakshi', '2017-07-10', 'Networking', 'I'),
    (3, 'Nira', '2017-05-22', 'MySQL', 'I'),
    (4, 'Jagdish', '2017-06-10', 'DBMS', 'I'),
    (5, 'Jayashree', '2017-07-05', 'MySQL', 'I'),
    (6, 'Kiran', '2017-06-30', 'Java', 'I');
    
select * from Borrower;

-- | Roll_no | Name      | DateOfIssue | NameOfBook  | Status |
-- |---------|-----------|-------------|-------------|--------|
-- | 1       | Amita     | 2017-06-25  | Java        | I      |
-- | 2       | Sonakshi  | 2017-07-10  | Networking  | I      |
-- | 3       | Nira      | 2017-05-22  | MySQL       | I      |
-- | 4       | Jagdish   | 2017-06-10  | DBMS        | I      |
-- | 5       | Jayashree | 2017-07-05  | MySQL       | I      |
-- | 6       | Kiran     | 2017-06-30  | Java        | I      |


-- To find difference in current date and issue date
delimiter $
DROP PROCEDURE IF EXISTS P1;
Create  procedure P1(In rno1 int(3),name1 varchar(30))
begin
	Declare i_date date;
	Declare diff int;
	select DateofIssue into i_date from Borrower where  Roll_no =rno1
	and NameOfBook=name1;
	SELECT DATEDIFF(CURDATE(), i_date) into diff; --The DATEDIFF() function returns the difference in days between two date values.
end;
$
delimiter ;

call p1(1,'JAVA');

-- To change status from I to R
delimiter $
Create procedure P2(In rno1 int(3),name1 varchar(30))
begin
  Declare i_date date;
  Declare diff int;
  select DateofIssue into i_date from Borrower where Roll_no=rno1
  and NameOfBook=name1;
  SELECT DATEDIFF(CURDATE(), i_date) into diff;
  If diff>15 then
    Update Borrower
    set status='R'
    where Roll_no=rno1 and NameOfBook=name1;
  End if;
End;
$
delimiter ;

call p2(1,'JAVA');
select * from Borrower;

-- | Roll_no | Name      | DateOfIssue | NameOfBook  | Status |
-- |---------|-----------|-------------|-------------|--------|
-- | 1       | Amita     | 2017-06-25  | Java        | R      |
-- | 2       | Sonakshi  | 2017-07-10  | Networking  | I      |
-- | 3       | Nira      | 2017-05-22  | MySQL       | I      |
-- | 4       | Jagdish   | 2017-06-10  | DBMS        | I      |
-- | 5       | Jayashree | 2017-07-05  | MySQL       | I      |
-- | 6       | Kiran     | 2017-06-30  | Java        | I      |

-- To set fine amount between 15 and 30 days with status change


---To
-- set fine amount between 15 and 30 days & > 30
-- days with status change
delimiter $
DROP PROCEDURE IF EXISTS P3;
Create procedure P3(In rno1 int(3),name1 varchar(30))
begin
	Declare i_date date;
	Declare diff int;
	Declare fine_amt int;
    
	select dateOfIssue into i_date from Borrower where Roll_no=rno1 and Name=name1;
	SELECT DATEDIFF(CURDATE(), i_date) into diff;

	If (diff>=15 and diff<=30)then
		SET fine_amt=diff*5;
		insert into Fine values(rno1,CURDATE(),fine_amt);
	elseif (diff>30) then
		SET fine_amt=diff*50;
		insert into Fine values(rno1,CURDATE(),fine_amt);
	End if;
    	Update Borrower set status='R' where Roll_no=rno1 and Name=name1;
End;
$
call p3(3,'Nira');

--Fine table after p3
-- | Roll_no | Date      | Amt   |
-- |    3	   |2024-10-31 | 135950|

--Borrower table after p3
-- | Roll_no | Name      | DateOfIssue | NameOfBook  | Status |
-- |---------|-----------|-------------|-------------|--------|
-- | 1       | Amita     | 2017-06-25  | Java        | R      |
-- | 2       | Sonakshi  | 2017-07-10  | Networking  | I      |
-- | 3       | Nira      | 2017-05-22  | MySQL       | R      |
-- | 4       | Jagdish   | 2017-06-10  | DBMS        | I      |
-- | 5       | Jayashree | 2017-07-05  | MySQL       | I      |
-- | 6       | Kiran     | 2017-06-30  | Java        | I      |
