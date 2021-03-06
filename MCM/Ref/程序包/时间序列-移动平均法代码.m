function [floaver3,floaver5]= floataver(Y)
%Y:原时间序列
%floaver3,floaver5: 三点/五点移动平均值
n=length(Y);
%计算三点移动平均值
floaver3(1)=0;
floaver3(2)=0;
floaver3(3)=0;
for i=4:n
    floaver3(i)=(Y(i-1)+Y(i-2)+Y(i-3))/3;
end
%计算五点移动平均值
floaver5(1)=0;
floaver5(2)=0;
floaver5(3)=0;
floaver5(4)=0;
floaver5(5)=0;
for i=6:n
    floaver5(i)=(Y(i-1)+Y(i-2)+Y(i-3)+Y(i-4)+Y(i-5))/5;
end
end