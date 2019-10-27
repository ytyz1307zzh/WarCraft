#include<iostream> 
#include<cstring>
#include<iomanip>
using namespace std;
class npc
{
public:
	char *warrior[5];             //武士顺序
	int price[5];                //武士单价
	int attack[5];                //武士攻击力顺序，为常量
	int element;                 //生命元剩余量
	int total;                  //总人数（编号）,从1开始
	int species[100];           //所有武士的种类
	int life[100];              //武士的剩余生命值
	int power[100];             //武士的攻击力
	int location[100];          //武士当前所在地点
	double morale[100];         //士气值
	int loyalty[100];         //忠诚值
	int sword[100];             //是否有sword
	int bomb[100];              //是否有bomb
	int arrow[100];             //是否有arrow以及剩余几支arrow
	bool alive[100];           //是否存活在战场上
	npc(int i,int a,int b,int c,int d,int e,int m,int n,int p,int q,int r)
	{
		element=i;total=0;
		price[0]=a;price[1]=b;price[2]=c;price[3]=d;price[4]=e;
		attack[0]=m;attack[1]=n;attack[2]=p;attack[3]=q;attack[4]=r;
		memset(morale,0,sizeof(morale));
		memset(loyalty,0,sizeof(loyalty));
		memset(sword,0,sizeof(sword));
		memset(bomb,0,sizeof(bomb));
		memset(arrow,0,sizeof(arrow));
		memset(life,0,sizeof(life));
		memset(power,0,sizeof(power));
		for(int j=0;j<100;j++)
			alive[j]=false;
	}
};
class CITY
{
public:
	int rednum;                 //城市中红士兵的编号
	int bluenum;                //城市中蓝士兵的编号
	int flag;                   //插着谁的旗子，0为没有，1为红色旗子，2为蓝色旗子
	int fight[100];             //记录战斗结果，0为平局，1为红方胜，2为蓝方胜
	int fightnum;               //战斗编号,从1开始
	int element;                //城市中生产的生命元
	int enemy;                  //司令部中敌人数量
	CITY()
	{
		flag=0;enemy=0;fightnum=0;
		rednum=0;bluenum=0;element=0;
	}
};
void produce(npc & side,int & sidei,const int i,const int N,const int hour)//i表示红方还是蓝方,sidei为武士种类的循环变量,取值为0—4，和species对应
{
	if(side.element>=side.price[sidei])
	{
		side.element-=side.price[sidei];//生命元扣除
		side.total++;//总数+1，即武士编号
		side.species[side.total]=sidei;//记录种类
		side.life[side.total]=side.price[sidei];
		side.power[side.total]=side.attack[sidei];
		side.alive[side.total]=true;
		printf("%03d",hour);
		cout<<":00";
		if(i==1)
		{
			cout<<" red "<<side.warrior[sidei]<<" "<<side.total<<" born"<<endl;
			side.location[side.total]=0;	
			if(sidei==4)
			{
				side.morale[side.total]=(double)side.element/(double)side.price[4];
				cout<<"Its morale is "<<fixed<<setprecision(2)<<side.morale[side.total]<<endl;
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
			else if(sidei==1)
			{
				side.loyalty[side.total]=side.element;
				cout<<"Its loyalty is "<<side.loyalty[side.total]<<endl;
			}
			else if(sidei==3)
			{
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
				switch((side.total+1)%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
			else if(sidei==0)
			{
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
		}
		else if(i==2)
		{
			cout<<" blue "<<side.warrior[sidei]<<" "<<side.total<<" born"<<endl;
			side.location[side.total]=N+1;
			if(sidei==1)
			{
				side.morale[side.total]=(double)side.element/(double)side.price[1];
				cout<<"Its morale is "<<fixed<<setprecision(2)<<side.morale[side.total]<<endl;
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
			else if(sidei==0)
			{
				side.loyalty[side.total]=side.element;
				cout<<"Its loyalty is "<<side.loyalty[side.total]<<endl;
			}
			else if(sidei==2)
			{
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
				switch((side.total+1)%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
			else if(sidei==3)
			{
				switch(side.total%3)
				{
					case 0:side.sword[side.total]=side.power[side.total]/5;break;
					case 1:side.bomb[side.total]=1;break;
					case 2:side.arrow[side.total]=3;break;
				}
			}
		}
		sidei++;
		if(sidei==5)sidei=0;
	}
}
void escape(npc & side,const int i,const int hour,const int N)//i表示红方还是蓝方
{
	if(i==1)
	{
		for(int j=1;j<=side.total;j++)
			if(side.species[j]==1&&side.loyalty[j]<=0&&side.location[j]!=N+1&&side.alive[j]==true)
			{
				side.alive[j]=false;
				printf("%03d",hour);
				cout<<":05";
				cout<<" red lion "<<j<<" ran away"<<endl;
			}
	}
	else if(i==2)
	{
		for(int j=1;j<=side.total;j++)
			if(side.species[j]==0&&side.loyalty[j]<=0&&side.location[j]!=0&&side.alive[j]==true)
			{
				side.alive[j]=false;
				printf("%03d",hour);
				cout<<":05";
				cout<<" blue lion "<<j<<" ran away"<<endl;
			}
	}
}
void moveforward(npc & red,npc & blue,CITY* & city,const int hour,const int N,const int K,bool & redwin,bool & bluewin)//i表示红方还是蓝方
{
	int redflag=0,blueflag=0;//司令部是否有人进入，判断是否需要输出
		for(int j=1;j<=red.total;j++)
		{
			if(red.alive[j]==false)continue;
			if(red.location[j]==N+1)continue;
			red.location[j]++;
			city[red.location[j]].rednum=j;
			if(red.location[j]%2==0&&red.species[j]==0)//iceman每两步会掉血
			{
				if(red.life[j]<=9)
					red.life[j]=1;
				else
					red.life[j]-=9;
				red.power[j]+=20;
			}
			if(red.location[j]==N+1)//如果走到司令部做标记
			{
				city[N+1].enemy++;
				blueflag=1;
			}
		}
		for(int j=1;j<=blue.total;j++)
		{
			if(blue.alive[j]==false)continue;
			if(blue.location[j]==0)continue;
			blue.location[j]--;
			city[blue.location[j]].bluenum=j;
			if((N+1-blue.location[j])%2==0&&blue.species[j]==3)//iceman每两步会掉血
			{
				if(blue.life[j]<=9)
					blue.life[j]=1;
				else
					blue.life[j]-=9;
				blue.power[j]+=20;
			}
			if(blue.location[j]==0)//如果走到司令部做标记
			{
				city[0].enemy++;
				redflag=1;
			}
		}
	
	if(redflag==1)//如果前进事件发生在司令部
	{
		printf("%03d",hour);
		cout<<":10";
		cout<<" blue "<<blue.warrior[blue.species[city[0].bluenum]]<<" "<<city[0].bluenum<<" reached red headquarter with ";
		cout<<blue.life[city[0].bluenum]<<" elements and force "<<blue.power[city[0].bluenum]<<endl;
	}
	if(city[0].enemy==2)
	{
		printf("%03d",hour);
		cout<<":10 red headquarter was taken"<<endl;
		bluewin=true;
	}
	for(int j=1;j<=N;j++)
	{
		if(city[j].rednum>0&&red.alive[city[j].rednum]==true)
		{
			printf("%03d",hour);
			cout<<":10";
			cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" marched to city "<<j<<" with ";
			cout<<red.life[city[j].rednum]<<" elements and force "<<red.power[city[j].rednum]<<endl;
		}
		if(city[j].bluenum>0&&blue.alive[city[j].bluenum]==true)
		{
			printf("%03d",hour);
			cout<<":10";
			cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" marched to city "<<j<<" with ";
			cout<<blue.life[city[j].bluenum]<<" elements and force "<<blue.power[city[j].bluenum]<<endl;
		}
	}
	if(blueflag==1)//如果前进事件发生在司令部
	{
		printf("%03d",hour);
		cout<<":10";
		cout<<" red "<<red.warrior[red.species[city[N+1].rednum]]<<" "<<city[N+1].rednum<<" reached blue headquarter with ";
		cout<<red.life[city[N+1].rednum]<<" elements and force "<<red.power[city[N+1].rednum]<<endl;
	}
	if(city[N+1].enemy==2)
	{
		printf("%03d",hour);
		cout<<":10 blue headquarter was taken"<<endl;
		redwin=true;
	}
}
void cityproduce(CITY* & city,const int N)
{
	for(int j=1;j<=N;j++)
		city[j].element+=10;
}
void collectelement(npc & red,npc & blue,CITY* & city,const int N,const int hour)
{
	for(int j=1;j<=N;j++)
	{
		if(city[j].rednum!=0&&city[j].bluenum==0&&red.alive[city[j].rednum]==true)//判断城市中是否有人可以拿走生命元
		{
			red.element+=city[j].element;
			printf("%03d",hour);
			cout<<":30";
			cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" earned "<<city[j].element<<" elements for his headquarter"<<endl;
			city[j].element=0;
		}
		else if(city[j].rednum==0&&city[j].bluenum!=0&&blue.alive[city[j].bluenum]==true)
		{
			blue.element+=city[j].element;
			printf("%03d",hour);
			cout<<":30";
			cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" earned "<<city[j].element<<" elements for his headquarter"<<endl;
			city[j].element=0;
		}
	}
}
void shoot(npc & red,npc & blue,CITY* & city,const int N,const int hour,const int R)
{
	for(int j=1;j<=N;j++)
	{
		if(city[j].rednum!=0&&city[j+1].bluenum!=0&&j!=N&&red.arrow[city[j].rednum]>0&&blue.alive[city[j+1].bluenum]==true)
			//确认下一个城市有敌人、arrow没用光，自己和敌人都活着
		{
			printf("%03d",hour);
			cout<<":35";
			cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" shot";
			red.arrow[city[j].rednum]--;//arrow个数减少一个
			blue.life[city[j+1].bluenum]-=R;
			if(blue.life[city[j+1].bluenum]<=0)
			{
				cout<<" and killed blue "<<blue.warrior[blue.species[city[j+1].bluenum]]<<" "<<city[j+1].bluenum;
				blue.alive[city[j+1].bluenum]=false;
			}
			cout<<endl;
		}
		if(city[j].bluenum!=0&&city[j-1].rednum!=0&&j!=1&&blue.arrow[city[j].bluenum]>0&&red.alive[city[j-1].rednum]==true)
		{
			printf("%03d",hour);
			cout<<":35";
			cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" shot";
			blue.arrow[city[j].bluenum]--;
			red.life[city[j-1].rednum]-=R;
			if(red.life[city[j-1].rednum]<=0)
			{
				cout<<" and killed red "<<red.warrior[red.species[city[j-1].rednum]]<<" "<<city[j-1].rednum;
				red.alive[city[j-1].rednum]=false;
			}
			cout<<endl;
		}
	}
	for(int j=1;j<=N;j++)
	{
		if(red.alive[city[j].rednum]==true&&blue.alive[city[j].bluenum]==false&&city[j].bluenum!=0)
		{
			city[j].fightnum++;
			city[j].fight[city[j].fightnum]=1;
		}
		else if(red.alive[city[j].rednum]==false&&blue.alive[city[j].bluenum]==true&&city[j].rednum!=0)
		{
			city[j].fightnum++;
			city[j].fight[city[j].fightnum]=2;
		}
	}
}
int simulantfight(npc red,npc blue,const int rednum,const int bluenum,CITY & city,const int citynum)
	//citynum是城市编号,平局返回0
{
	int initial=0;//谁主动进攻，1为红方，2为蓝方
	if(city.flag==1||(city.flag==0&&citynum%2==1))initial=1;
	else if(city.flag==2||(city.flag==0&&citynum%2==0))initial=2;
	if(initial==1)//红方主动进攻
	{
		blue.life[bluenum]-=red.power[rednum];//蓝武士生命值减掉红武士的攻击值
		if(red.sword[rednum]!=0)
			blue.life[bluenum]-=red.sword[rednum];//蓝武士生命值减掉红武士sword的攻击值
		if(blue.life[bluenum]<=0)    //如果蓝武士被杀死
			return 1;      //红方获胜返回1
		else if(blue.species [bluenum]!=2)    //蓝武士没死并且不是ninja，开始反击
		{
			red.life[rednum]-=(blue.power[bluenum]/2);
			if(blue.sword[bluenum]!=0)
				red.life[rednum]-=blue.sword[bluenum];
			if(red.life[rednum]<=0)
				return 2;     //蓝方获胜返回2
			else return 0;
		}
		else return 0;
	}
	else if(initial==2)//蓝方主动进攻
	{
		red.life[rednum]-=blue.power[bluenum];
		if(blue.sword[bluenum]!=0)
			red.life[rednum]-=blue.sword[bluenum];
		if(red.life[rednum]<=0)
			return 2;
		else if(red.species[rednum]!=3)
		{
			blue.life[bluenum]-=(red.power[rednum]/2);
			if(red.sword[rednum]!=0)
				blue.life[bluenum]-=red.sword[rednum];
			if(blue.life[bluenum]<=0) 
				return 1;
			else return 0;
		}
		else return 0;
	}
	return 0;
}
void usebomb(npc & red,npc & blue,CITY* & city,const int N,const int hour)
{
	for(int j=1;j<=N;j++)
	{
		if(city[j].rednum>0&&city[j].bluenum>0&&red.alive[city[j].rednum]==true&&blue.alive[city[j].bluenum]==true)
		{
			if(red.bomb[city[j].rednum]==1&&simulantfight(red,blue,city[j].rednum,city[j].bluenum,city[j],j)==2)
			{
				red.life[city[j].rednum]=0;red.alive[city[j].rednum]=false;
				blue.life[city[j].bluenum]=0;blue.alive[city[j].bluenum]=false;
				printf("%03d",hour);
				cout<<":38";
				cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum;
				cout<<" used a bomb and killed blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<endl;
			}
			else if(blue.bomb[city[j].bluenum]==1&&simulantfight(red,blue,city[j].rednum,city[j].bluenum,city[j],j)==1)
			{
				red.life[city[j].rednum]=0;red.alive[city[j].rednum]=false;
				blue.life[city[j].bluenum]=0;blue.alive[city[j].bluenum]=false;
				printf("%03d",hour);
				cout<<":38";
				cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum;
				cout<<" used a bomb and killed red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<endl;
			}
		}
	}
}
void fight(npc & red,npc & blue,CITY* & city,const int N,const int hour)
	//citynum是城市编号,平局返回0
{
	for(int j=1;j<=N;j++)
	{
		if(red.alive[city[j].rednum]==true&&blue.alive[city[j].bluenum]==true)
		{
			int redlife=red.life[city[j].rednum],bluelife=blue.life[city[j].bluenum];//储存初始生命值，便于lion死亡后给对方
			int initial;//谁主动进攻，1为红方，2为蓝方
			if(city[j].flag==1||(city[j].flag==0&&j%2==1))initial=1;
			else if(city[j].flag==2||(city[j].flag==0&&j%2==0))initial=2;
			if(initial==1)//红方主动进攻
			{
				blue.life[city[j].bluenum]-=red.power[city[j].rednum];//蓝武士生命值减掉红武士的攻击值
				if(red.sword[city[j].rednum]!=0)
				{
					blue.life[city[j].bluenum]-=red.sword[city[j].rednum];//蓝武士生命值减掉红武士sword的攻击值
					red.sword[city[j].rednum]=(red.sword[city[j].rednum]*4)/5;
				}
				printf("%03d",hour);
				cout<<":40";
				cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" attacked blue ";
				cout<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" in city "<<j;
				cout<<" with "<<red.life[city[j].rednum]<<" elements and force "<<red.power[city[j].rednum]<<endl;
				if(blue.life[city[j].bluenum]<=0)    //如果蓝武士被杀死
				{
					printf("%03d",hour);
					cout<<":40";
					cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" was killed in city "<<j<<endl;
					blue.alive[city[j].bluenum]=false;
					city[j].fightnum++;
					city[j].fight[city[j].fightnum]=1;
					if(blue.species[city[j].bluenum]==0)
						red.life[city[j].rednum]+=bluelife;
				}
				else if(blue.species [city[j].bluenum]!=2)    //蓝武士没死并且不是ninja，开始反击
				{
					red.life[city[j].rednum]-=(blue.power[city[j].bluenum]/2);
					if(blue.sword[city[j].bluenum]!=0)
					{
						red.life[city[j].rednum]-=blue.sword[city[j].bluenum];
						blue.sword[city[j].bluenum]=(blue.sword[city[j].bluenum]*4)/5;
					}
					printf("%03d",hour);
					cout<<":40";
					cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" fought back against red ";
					cout<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" in city "<<j<<endl;
					if(red.life[city[j].rednum]<=0)//红武士被反击的蓝武士打死
					{
						printf("%03d",hour);
						cout<<":40";
						cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" was killed in city "<<j<<endl;
						red.alive[city[j].rednum]=false;
						city[j].fightnum++;
						city[j].fight[city[j].fightnum]=2;
						if(red.species[city[j].rednum]==1)
							blue.life[city[j].bluenum]+=redlife;
					}
				}
			}
			else if(initial==2)//蓝方主动进攻
			{
				red.life[city[j].rednum]-=blue.power[city[j].bluenum];
				if(blue.sword[city[j].bluenum]!=0)
				{
					red.life[city[j].rednum]-=blue.sword[city[j].bluenum];
					blue.sword[city[j].bluenum]=(blue.sword[city[j].bluenum]*4)/5;
				}
				printf("%03d",hour);
				cout<<":40";
				cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" attacked red ";
				cout<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" in city "<<j;
				cout<<" with "<<blue.life[city[j].bluenum]<<" elements and force "<<blue.power[city[j].bluenum]<<endl;
				if(red.life[city[j].rednum]<=0)//红武士被打死
				{
					printf("%03d",hour);
					cout<<":40";
					cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" was killed in city "<<j<<endl;
					red.alive[city[j].rednum]=false;
					city[j].fightnum++;
					city[j].fight[city[j].fightnum]=2;
					if(red.species[city[j].rednum]==1)
						blue.life[city[j].bluenum]+=redlife;
				}
				else if(red.species[city[j].rednum]!=3)//不是ninja,开始反击
				{
					blue.life[city[j].bluenum]-=(red.power[city[j].rednum]/2);
					printf("%03d",hour);
					cout<<":40";
					cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" fought back against blue ";
					cout<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" in city "<<j<<endl;
					if(red.sword[city[j].rednum]!=0)
					{
						blue.life[city[j].bluenum]-=red.sword[city[j].rednum];
						red.sword[city[j].rednum]=(red.sword[city[j].rednum]*4)/5;
					}
					if(blue.life[city[j].bluenum]<=0) //蓝武士被反击的红武士打死
					{
						printf("%03d",hour);
						cout<<":40";
						cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" was killed in city "<<j<<endl;
						blue.alive[city[j].bluenum]=false;
						city[j].fightnum++;
						city[j].fight[city[j].fightnum]=1;
						if(blue.species[city[j].bluenum]==0)
							red.life[city[j].rednum]+=bluelife;
					}
				}
			}
			if(red.alive[city[j].rednum]==true&&blue.alive[city[j].bluenum]==true)
			{
				city[j].fightnum++;
				city[j].fight[city[j].fightnum]=0;
			}
		}
		if(city[j].fight[city[j].fightnum]==1&&red.species[city[j].rednum]==4&&red.alive[city[j].rednum]==true&&city[j].bluenum>0)//判断红方
			red.morale[city[j].rednum]+=0.2;
		else if(city[j].fight[city[j].fightnum]==0&&red.species[city[j].rednum]==4&&red.alive[city[j].rednum]==true&&city[j].bluenum>0)
			red.morale[city[j].rednum]-=0.2;
		if(city[j].fight[city[j].fightnum]!=2&&red.species[city[j].rednum]==4&&red.alive[city[j].rednum]==true&&red.morale[city[j].rednum]>0.8&&(city[j].flag==1||(city[j].flag==0&&j%2==1))&&city[j].bluenum>0)
			//判断是dragon,士气大于0.8，是主动进攻（旗子为红色或者编号为奇数）
		{
			printf("%03d",hour);
			cout<<":40";
			cout<<" red dragon "<<city[j].rednum<<" yelled in city "<<j<<endl;
		}
		if(city[j].fight[city[j].fightnum]==2&&blue.species[city[j].bluenum]==1&&blue.alive[city[j].bluenum]==true&&city[j].rednum>0)//判断蓝方
			blue.morale[city[j].bluenum]+=0.2;
		else if(city[j].fight[city[j].fightnum]==0&&blue.species[city[j].bluenum]==1&&blue.alive[city[j].bluenum]==true&&city[j].rednum>0)
			blue.morale[city[j].bluenum]-=0.2;
		if(city[j].fight[city[j].fightnum]!=1&&blue.species[city[j].bluenum]==1&&blue.alive[city[j].bluenum]==true&&blue.morale[city[j].bluenum]>0.8&&(city[j].flag==2||(city[j].flag==0&&j%2==0))&&city[j].rednum>0)
			//判断是dragon,士气大于0.8，是主动进攻（旗子为红色或者编号为奇数）
		{
			printf("%03d",hour);
			cout<<":40";
			cout<<" blue dragon "<<city[j].bluenum<<" yelled in city "<<j<<endl;
		}
		if(city[j].fight[city[j].fightnum]==1&&red.alive[city[j].rednum]==true&&city[j].bluenum!=0)//判断城市中是否有人可以拿走生命元
		{
			red.element+=city[j].element;
			printf("%03d",hour);
			cout<<":40";
			cout<<" red "<<red.warrior[red.species[city[j].rednum]]<<" "<<city[j].rednum<<" earned "<<city[j].element<<" elements for his headquarter"<<endl;
			city[j].element=0;
		}
		else if(city[j].fight[city[j].fightnum]==2&&blue.alive[city[j].bluenum]==true&&city[j].rednum!=0)
		{
			blue.element+=city[j].element;
			printf("%03d",hour);
			cout<<":40";
			cout<<" blue "<<blue.warrior[blue.species[city[j].bluenum]]<<" "<<city[j].bluenum<<" earned "<<city[j].element<<" elements for his headquarter"<<endl;
			city[j].element=0;
		}
		if(city[j].flag!=1&&city[j].fightnum>1&&city[j].fight[city[j].fightnum]==1&&city[j].fight[city[j].fightnum-1]==1)
		//判断红方是否升旗，之前没有红旗，连续两场红方胜
		{
			city[j].flag=1;
			printf("%03d",hour);
			cout<<":40";
			cout<<" red flag raised in city "<<j<<endl;
		}
		if(city[j].flag!=2&&city[j].fightnum>1&&city[j].fight[city[j].fightnum]==2&&city[j].fight[city[j].fightnum-1]==2)
		//判断蓝方是否升旗，之前没有蓝旗，连续两场蓝方胜
		{
			city[j].flag=2;
			printf("%03d",hour);
			cout<<":40";
			cout<<" blue flag raised in city "<<j<<endl;
		}
	}
}
void getreward(npc & red,npc & blue,CITY* & city,const int N)
{
	for(int j=N;j>=1;j--)//红方奖励
	{
		if(red.alive[city[j].rednum]==true&&city[j].fight[city[j].fightnum]==1&&red.element>=8&&city[j].bluenum>0)//判断是否是刚发生的战斗，所以判断bluenum是否是0
		{
			red.element-=8;
			red.life[city[j].rednum]+=8;
		}
	}
	for(int j=1;j<=N;j++)//蓝方奖励
	{
		if(blue.alive[city[j].bluenum]==true&&city[j].fight[city[j].fightnum]==2&&blue.element>=8&&city[j].rednum>0)//判断是否是刚发生的战斗，所以判断bluenum是否是0
		{
			blue.element-=8;
			blue.life[city[j].bluenum]+=8;
		}
	}
}
void loyaltychange(npc & red,npc & blue,CITY* & city,const int N,const int K)
{
	for(int j=1;j<=N;j++)
	{
		if(red.alive[city[j].rednum]==true&&city[j].fight[city[j].fightnum]==0&&red.species[city[j].rednum]==1&&city[j].bluenum!=0)//判断红方lion,存活并且没杀死敌人
			red.loyalty[city[j].rednum]-=K;
		if(blue.alive[city[j].bluenum]==true&&city[j].fight[city[j].fightnum]==0&&blue.species[city[j].bluenum]==0&&city[j].rednum!=0)//判断蓝方lion,存活并且没杀死敌人
			blue.loyalty[city[j].bluenum]-=K;
	}
}
void collectweapon(npc & red,npc & blue,CITY* & city,const int N)
{
	for(int j=1;j<=N;j++)
	{
		if(city[j].fight[city[j].fightnum]==1&&red.species[city[j].rednum]==2&&red.alive[city[j].rednum]==true&&city[j].bluenum!=0)
			//判断红方wolf,红方胜利，是wolf且存活，没有sword或者arrow
		{
			if(red.arrow[city[j].rednum]<=0&&blue.arrow[city[j].bluenum]>0)
				red.arrow[city[j].rednum]=blue.arrow[city[j].bluenum];
			if(red.sword[city[j].rednum]<=0&&blue.sword[city[j].bluenum]>0)
				red.sword[city[j].rednum]=blue.sword[city[j].bluenum];
			if(red.bomb[city[j].rednum]==0&&blue.bomb[city[j].bluenum]==1)
				red.bomb[city[j].rednum]=blue.bomb[city[j].bluenum];
		}
		if(city[j].fight[city[j].fightnum]==2&&blue.species[city[j].bluenum]==4&&blue.alive[city[j].bluenum]==true&&city[j].rednum!=0)
			//判断蓝方wolf,红方胜利，是wolf且存活，没有sword或者arrow
		{
			if(blue.arrow[city[j].bluenum]<=0&&red.arrow[city[j].rednum]>0)
				blue.arrow[city[j].bluenum]=red.arrow[city[j].rednum];
			if(blue.sword[city[j].bluenum]<=0&&red.sword[city[j].rednum]>0)
				blue.sword[city[j].bluenum]=red.sword[city[j].rednum];
			if(blue.bomb[city[j].bluenum]==0&&red.bomb[city[j].rednum]==1)
				blue.bomb[city[j].bluenum]=red.bomb[city[j].rednum];
		}
	}
}
void reset0(npc & red,npc & blue,CITY* & city,const int N)//清空城市中武士编号，避免影响后续的战斗
{
	for(int j=1;j<=N;j++)
	{
		city[j].rednum=0;
		city[j].bluenum=0;
	}
}
void elementreport(npc & red,npc & blue,const int hour)
{
	printf("%03d",hour);
	cout<<":50";
	cout<<" "<<red.element<<" elements in red headquarter"<<endl;
	printf("%03d",hour);
	cout<<":50";
	cout<<" "<<blue.element<<" elements in blue headquarter"<<endl;
}
void weaponreport(npc & red,npc & blue,const int hour)
{
	for(int j=red.total;j>=1;j--)
	{
		int weaponnum=0;
		if(red.alive[j]==false)continue;
		printf("%03d",hour);
		cout<<":55";
		cout<<" red "<<red.warrior[red.species[j]]<<" "<<j<<" has ";
		if(red.arrow[j]>0)
		{
			cout<<"arrow("<<red.arrow[j]<<")";
			weaponnum++;
		}
		if(red.bomb[j]==1&&weaponnum==0)
		{
			cout<<"bomb";
			weaponnum++;
		}
		else if(red.bomb[j]==1&&weaponnum!=0)
		{
			cout<<",bomb";
			weaponnum++;
		}
		if(red.sword[j]>0&&weaponnum==0)
		{
			cout<<"sword("<<red.sword[j]<<")";
			weaponnum++;
		}
		else if(red.sword[j]>0&&weaponnum!=0)
		{
			cout<<",sword("<<red.sword[j]<<")";
			weaponnum++;
		}
		if(weaponnum==0)
			cout<<"no weapon";
		cout<<endl;
	}
	for(int j=1;j<=blue.total;j++)
	{
		int weaponnum=0;
		if(blue.alive[j]==false)continue;
		printf("%03d",hour);
		cout<<":55";
		cout<<" blue "<<blue.warrior[blue.species[j]]<<" "<<j<<" has ";
		if(blue.arrow[j]>0)
		{
			cout<<"arrow("<<blue.arrow[j]<<")";
			weaponnum++;
		}
		if(blue.bomb[j]==1&&weaponnum==0)
		{
			cout<<"bomb";
			weaponnum++;
		}
		else if(blue.bomb[j]==1&&weaponnum!=0)
		{
			cout<<",bomb";
			weaponnum++;
		}
		if(blue.sword[j]>0&&weaponnum==0)
		{
			cout<<"sword("<<blue.sword[j]<<")";
			weaponnum++;
		}
		else if(blue.sword[j]>0&&weaponnum!=0)
		{
			cout<<",sword("<<blue.sword[j]<<")";
			weaponnum++;
		}
		if(weaponnum==0)
			cout<<"no weapon";
		cout<<endl;
	}
}
int main() 
{ 
	//freopen("C:\\Users\\Zhihan Zhang\\Desktop\\1.txt", "w", stdout);
	int cases;                   //测试组数
	cin>>cases;
	for(int i=1;i<=cases;i++)
	{
		cout<<"Case "<<i<<":"<<endl;
		int time;                   //剩余时间
		int M,N,R,K;                 //初始生命元，城市数量，arrow攻击力，忠诚度降低量
		int life1,life2,life3,life4,life5;//五种武士的初始生命值
		int power1,power2,power3,power4,power5;//五种武士的攻击力
		cin>>M>>N>>R>>K>>time;
		cin>>life1>>life2>>life3>>life4>>life5>>power1>>power2>>power3>>power4>>power5;
		npc red(M,life3,life4,life5,life2,life1,power3,power4,power5,power2,power1);
		npc blue(M,life4,life1,life2,life3,life5,power4,power1,power2,power3,power5);
		red.warrior[0]="iceman";red.warrior[1]="lion";red.warrior[2]="wolf";red.warrior[3]="ninja";red.warrior[4]="dragon";
		blue.warrior[0]="lion";blue.warrior[1]="dragon";blue.warrior[2]="ninja";blue.warrior[3]="iceman";blue.warrior[4]="wolf";
		CITY* city=new CITY[N+2];
		int redi=0,bluei=0;//武士种类循环变量
		int hour=0;//时间变量，用于输出时间
		bool redwin=false,bluewin=false;
		for(;time>=0;hour++)
		{
			produce(red,redi,1,N,hour);
			produce(blue,bluei,2,N,hour);
			if(hour!=0)
			{
				time-=5;
				if(time<5){break;}
			}
			escape(red,1,hour,N);
			escape(blue,2,hour,N);
			time-=5;
			if(time<5){break;}
			moveforward(red,blue,city,hour,N,K,redwin,bluewin);
			if(redwin==true){break;}
			if(bluewin==true){break;}
			time-=5;
			if(time<10){break;}
			cityproduce(city,N);
			time-=10;
			if(time<10){break;}
			collectelement(red,blue,city,N,hour);
			time-=10;
			if(time<5){break;}
			shoot(red,blue,city,N,hour,R);
			time-=5;
			if(time<3){break;}
			usebomb(red,blue,city,N,hour);
			time-=3;
			if(time<2){break;}
			fight(red,blue,city,N,hour);
			getreward(red,blue,city,N);
			loyaltychange(red,blue,city,N,K);
			collectweapon(red,blue,city,N);
			reset0(red,blue,city,N);
			time-=2;
			if(time<10){break;}
			elementreport(red,blue,hour);
			time-=10;
			if(time<5){break;}
			weaponreport(red,blue,hour);
			time-=5;
			if(time<5){break;}
		}
	}
	return 0;
}