一维插值步骤
（1）输入已知数据，x,y
（2）输入待插自变量的值x1
x=1:12;
y=[5 8 9 15 25 29 31 30 22 25 27 24];
x1=1:0.1:12;t=interp1(x,y,x1,'spline');%
 plot(x1,t,'r:')   %作图
xlabel('x'),ylabel('y')

二维插值步骤
（1）先输入二维数据的x,y坐标值
（2）输入Z数据
（3）输入待插点的x,y坐标
（4）应用函数插值即可
x=1:5;
y=1:3;
temps=[82 81 80 82 84;79 63 61 65 81;84 84 82 85 86];
mesh(x,y,temps);
xi=1:0.2:5;
yi=1:0.2:3;
zi=interp2(x,y,temps,xi',yi,'cubic');
mesh(xi,yi,zi);

多项式拟合步骤
(1)输入待拟合数据x,y
(2)输入函数公式进行拟合
x=0:0.1:1; 
y=[-0.447 1.978 3.28 6.16 7.08 7.34 7.66   9.56 9.48 9.30 11.2]; 
A=polyfit(x,y,2)

指定函数拟合步骤
 (1)输入待拟合数据x,y
（2）指定函数关系式
syms t;
x=[0;0.4;1.2;2;2.8;3.6;4.4;5.2;6;7.2;8;9.2;10.4;11.6;12.4;13.6;14.4;15];
y=[1;0.85;0.29;-0.27;-0.53;-0.4;-0.12;0.17;0.28;0.15;-0.03;-0.15;-0.071;0.059;0.09;0.032;-0.015;-0.02];%指定函数形式为f(t)=acos(kt)e^(wt),进行拟合
f=fittype('a*cos(k*t)*exp(w*t)','independent','t','coefficients',{'a','k','w'});
cfun=fit(x,y,f)     %显示拟合函数
xi=0:.1:20;
yi=cfun(xi);
plot(x,y,'r*',xi,yi,'b-');
