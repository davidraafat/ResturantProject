//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Rest\Motorcycle.h"
#include"Generic_DS\List.h"
#include"Generic_DS\Queue.h"
#include"Events\ArrivalEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include<fstream>
ORD_TYPE ChangeTypeOrd(char n)
{
	if(n=='N'){return TYPE_NRM;}
	else if(n=='V'){return TYPE_VIP;}
	else{return TYPE_FROZ;}
}
REGION ChangeTypeReg(char n)
{
	if(n=='A'){return A_REG;}
	else if(n=='B'){return B_REG;}
	else if(n=='C'){return C_REG;}
	else {return D_REG;}

}
void Read(Restaurant* R)
{
	
ArrivalEvent* ev;
CancellationEvent* ec;
PromotionEvent* ep;
ORD_TYPE ord;
REGION reg;
int time,id,dest,mon,extrMon;
int sn,sf,sv,n,f,v,timeProm,numEvent;
char typeEve,typeorder,typeReg;
R->getpGUI()->PrintMessage("enter file name please ");
ifstream myfile(R->getpGUI()->GetString()+".txt");

if(myfile.is_open())
 {
 myfile>>sn>>sf>>sv;
 myfile>>n>>f>>v;
	 R->getRegion(A_REG)->setmotorsinfo(sn,sf,sv,n,f,v);
	 
 myfile>>n>>f>>v;
	 R->getRegion(B_REG)->setmotorsinfo(sn,sf,sv,n,f,v);

 myfile>>n>>f>>v;
	 R->getRegion(C_REG)->setmotorsinfo(sn,sf,sv,n,f,v);

 myfile>>n>>f>>v;
	 R->getRegion(D_REG)->setmotorsinfo(sn,sf,sv,n,f,v);
	
	 myfile>>timeProm>>numEvent;////////
	 R->setTimeOrdPr(timeProm);
	 for(int i=0;i<numEvent;i++)//
	{
 myfile>>typeEve;
 if(typeEve=='R')
 {
 myfile>>time>>typeorder>>id>>dest>>mon>>typeReg;
 ord=ChangeTypeOrd(typeorder);
 reg=ChangeTypeReg(typeReg); 	 
 ev=new ArrivalEvent(time,ord,id,dest,mon,reg);
		R->AddEvent(ev);
 }
 else if(typeEve=='X')
 {
 myfile>>time>>id;
	 ec=new CancellationEvent(time,id);
	R->AddEvent(ec);
 }
 else if(typeEve=='P')
 {
	 myfile>>time>>id>>extrMon;
	 ep=new PromotionEvent(time,id,extrMon);
		R->AddEvent(ep);

 }
} 
	 myfile.close(); }
else {R->getpGUI()->PrintMessage("File cannot be opened");
} 
}
int main()
{
	
	Restaurant* pRest = new Restaurant;
	Read(pRest);
	pRest->RunSimulation();
	cout<<"function is ............read";
	delete pRest;
	
	system ("pause");
	return 0;
}
