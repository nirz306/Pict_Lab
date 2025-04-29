Create an EC instance -> set name (eg:web server) -> set os: Amazon Linux-> 64bit -> Free tire eligible -> T2 micro -> create new key pair -> launch instance  
Connect to EC2 instance-> EC2 instance method-> connect -> EC2 instance connect -> connect 

Terminal Commands

sudo su -
yum update -y 
yum  install -y httpd
systemctl status httpd
mkdir temp
cd temp/
# wget [link of the website in zip]
ls lrt
unzip complex.zip
cd complex
ls -lrt
mv * /var/www/html/
cd /var/www/html/
ls -lrt

Security -> system groupd -> Inbound roules -> edit -> add rules-> add http and https anywhere

systemctl status httpd 
systemctl enable httpd
systemctl start httpd
