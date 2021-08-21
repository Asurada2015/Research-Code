第一步：先将数据集展开
第二步：找到数据集的大小，也就是多少列或者多少行
第三步：将数据替换掉下面的数据，指的是cuspamax数据，即可（下方以1024行数据为例）

figure(1)
plot(cuspamax)
xlabel('时间');ylabel('幅值');
title('频率突变信号');
figure(2)
[c,l]=wavedec(cuspamax,5,'db6');
cfd=zeros(5,1024);
for  k=1:5
    d=detcoef(c,l,k);
    d=d(ones(1,2^k),:);
    cfd(k,:)=wkeep(d(:)',1024)
end
cfd=cfd(:);
I=find(abs(cfd)<sqrt(eps));
cfd(I)=zeros(size(I));
cfd=reshape(cfd,5,1024);
colormap(pink(64));
img=image(flipud(wcodemat(cfd,64,'row')));
set(get(img,'parent'),'YtickLabel',[]);
title('离散小波变换后系数的绝对值')
ylabel('层数');
figure(3)
ccfs=cwt(cuspamax,1:32,'haar','plot');
title('连续小波变换系数的绝对值')
colormap(pink(64));
ylabel('尺度')
xlabel('时间(或者空间)')