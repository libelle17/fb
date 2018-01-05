#include "kons.h"
#include "DB.h"
#define VOMHAUPTCODE
#include "fb.h"
#include "tr64.h"

enum T_
{
 T_zu_schreiben,
 T_VorgbAllg,
 T_VorgbSpeziell,
 T_MusterVorgb,
 T_rueckfragen,
 T_autokonfschreib,
 T_MAX
}; // enum T_

char const *DPROG_T[T_MAX+1][SprachZahl]={
 // T_zu_schreiben
 {"zu schreiben: ","must write: "},
 // T_VorgbAllg
 {"VorgbAllg()","generalprefs()"},
 // T_VorgbSpeziell
 {"VorgbSpeziell()","specialprefs()"},
 // T_MusterVorgb
 {"MusterVorgb()","sampleprefs"},
 // T_rueckfragen
 {"rueckfragen()","callbacks()"},
 // T_autokonfschreib
 {"autokonfschreib()","autoconfwrite()"},
 {"",""}
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);

uchar ZDB=0; // fuer Zusatz-Debugging (SQL): ZDB 1, sonst: 0
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen; muss dann auf lgp zeigen;

using namespace std;

hhcl::hhcl(const int argc, const char *const *const argv):hcl(argc,argv)
{
} // hhcl::hhcl

hhcl::~hhcl()
{
} // hhcl::~hhcl

// wird aufgerufen in: rueckfragen, als virtualle Funktion von hcl::gcl0()
void hhcl::lgnzuw()
{
 hcl::lgnzuw();
 Txd.lgn=Tx.lgn=Txk.lgn;
} // void hhcl::lgnzuw

// wird aufgerufen in: main
void hhcl::getcommandl0()
{
 if (obverb) {
  cout<<violett<<"getcommandl0()"<<schwarz<<endl;
  obverb=0;
 }
 // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
 const char* const sarr[]={"language"};
 agcnfA.initd(sarr,sizeof sarr/sizeof *sarr);
 gcl0();
} // getcommandl0

void hhcl::VorgbAllg()
{
 Log(violetts+Tx[T_VorgbAllg]+schwarz);
} // void hhcl::VorgbAllg

void hhcl::VorgbSpeziell()
{
 Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
 MusterVorgb();
} // void hhcl::VorgbSpeziell

void hhcl::MusterVorgb()
{
 Log(violetts+Tx[T_MusterVorgb]+schwarz);
} // void hhcl::MusterVorgb

// wird aufgerufen in: main
void hhcl::lieskonfein()
{
 // hcl::lieskonfein();
 lfd++;
 setzlog();
 if (nrzf) rzf=0;
} // void hhcl::lieskonfein

//wird aufgerufen in: main
int hhcl::getcommandline()
{
 Log(violetts+"getcommandline()"+schwarz);
 return 0;
} // int hhcl::getcommandline

// wird aufgerufen in: main
void hhcl::rueckfragen()
{
 Log(violetts+Tx[T_rueckfragen]+schwarz);
 if (rzf) {
  int lfd=-1;
  const char *const locale = setlocale(LC_CTYPE,"");
  if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
  vector<string> sprachen={"e","d"/*,"f","i"*/};
  if (agcnfA[++lfd].wert.empty()||rzf) {
   langu=Tippstrs(sprachstr.c_str()/*"Language/Sprache/Lingue/Lingua"*/,&sprachen,&langu);
   lgnzuw();
   agcnfA[lfd].setze(&langu);
  } // if (agcnfA
 } // if (rzf)
} // void hhcl::rueckfragen()

// wird aufgerufen in: main
void hhcl::autokonfschreib()
{
 Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Txk[T_ja]:Txk[T_nein]));
 if (rzf||obkschreib) {
 } // if (rzf||obkschreib)
} // void hhcl::autokonfschreib

// wird aufgerufen in: main
void hhcl::zeigueberschrift()
{
 char buf[20]; snprintf(buf,sizeof buf,"%.5f",versnr);
 ::Log(schwarzs+Txk[T_Programm]+blau+mpfad+schwarz+", V: "+blau+buf+schwarz,1,1);
} // void hhcl::zeigueberschrift

int tuwas()
{
	tr64cl tr64("libelle17","bach17raga");
	//	tr64cl tr64("","");
	string buffer;
	string grund="http://fritz.box:49000";
	holurl(grund+"/tr64desc.xml",&buffer);
	size_t pos=0;
	string serviceh;
	int zeigalle=0;
	mdatei logf("fbausg.txt",ios::out,0);
	int oblog=logf.is_open();
	while ((pos=holraus(buffer,"service",&serviceh,pos))) {
		if (zeigalle) {
			caus<<endl;
		}
		if (oblog) logf<<endl;	
		string serviceType;
		holraus(serviceh,"serviceType",&serviceType);
		if (zeigalle) {
			caus<<"  serviceType: "<<dblau<<serviceType<<schwarz<<endl;
		}
		if (oblog) logf<<"  serviceType: "<<setw(70)<<serviceType<<endl;
		string serviceId;
		holraus(serviceh,"serviceId",&serviceId);
		if (zeigalle) {
			caus<<"  serviceId:   "<<dblau<<serviceId<<schwarz<<endl;
		}
		if (oblog) logf<<"  serviceId: "<<setw(70)<<serviceId<<endl;
		string controlURL;
		holraus(serviceh,"controlURL",&controlURL);
		if (zeigalle) {
			caus<<"  controlURL:  "<<dblau<<controlURL<<schwarz<<endl;
		}
		if (oblog) logf<<"  controlURL: "<<setw(70)<<controlURL<<endl;
		string SCPDURL;
		holraus(serviceh,"SCPDURL",&SCPDURL);
		if (zeigalle) {
			caus<<"  SCPDURL:     "<<dblau<<SCPDURL<<schwarz<<endl;
		}
		if (oblog) logf<<"  SCPDURL: "<<setw(70)<<SCPDURL<<endl;

		string ibuf;
		holurl(grund+SCPDURL,&ibuf);
		size_t ipos=0;
		string inurl;
		while ((ipos=holraus(ibuf,"action",&inurl,ipos))) {
			string action;
			holraus(inurl,"name",&action);
			if (zeigalle) {
				caus<<"  "<<violett<<action<<schwarz<<endl;
			}
			if (oblog) logf<<"  "<<setw(70)<<action<<endl; 
			size_t iipos=0;
			string iinurl;
			int keinin=1;
			vector<string>ausv;
			while ((iipos=holraus(inurl,"argument",&iinurl,iipos))) {
				string argdir,argname;
				holraus(iinurl,"direction",&argdir);
				holraus(iinurl,"name",&argname);
				if (argdir=="out") {
					ausv.push_back(argname);	
				} else {
					if (keinin) if (argdir=="in") keinin=0;
					if (zeigalle) {
						caus<<"    "<<dgrau<<argdir<<" "<<argname<<schwarz<<endl;
					}
					if (oblog) logf<<"   "<<argdir<<" "<<argname<<endl; 
				}
			}
			if (keinin && action.find("Get")!=string::npos) {
				string ubuf;
				tr64.fragurl(controlURL,serviceType,action,&ubuf);
				if (ubuf.find("invalid action")==string::npos) {
					for(size_t ausnr=0;ausnr<ausv.size();ausnr++) {
						string ergeb;
						holraus(ubuf,ausv[ausnr],&ergeb);
						if (zeigalle || !ergeb.empty()) {
							caus<<"    out "<<"   "<<(ergeb.empty()?schwarz:blau)<<setw(40)<<ausv[ausnr]+": "<<gruen<<ergeb<<schwarz<<endl;
						}
						if (oblog) logf<<"    out "<<"   "<<setw(40)<<ausv[ausnr]+": "<<ergeb<<endl;
						if (ergeb.find("sid=")!=string::npos) {
							string url2;
							holurl((ergeb[0]=='/'?tr64.FB:"")+ergeb,&url2);
							caus<<rot<<url2<<schwarz<<endl;
							if (oblog) logf<<url2<<endl;
						}
					}
				}
			} else {
				for(size_t ausnr=0;ausnr<ausv.size();ausnr++) {
					if (zeigalle) {
						caus<<"    out "<<"   "<<ausv[ausnr]<<endl;
					}
					if (oblog) logf<<"    out "<<"   "<<ausv[ausnr]<<endl;
				}
			} // 			if (keinin && action.find("Get")!=string::npos) else
		} // 		while ((ipos=holraus(ibuf,"action",&inurl,ipos)))
	} // 	while ((pos=holraus(buffer,"service",&serviceh,pos)))
	if (oblog) logf.close();
	return 0;
} // int tuwas()


int main(int argc,char** argv)
{
 hhcl hhi(argc,argv); // hiesige Hauptinstanz
 /*//
 if (argc>1) {
 } // (argc>1)
 */
 hhi.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
 hhi.VorgbAllg();
 if (hhi.obhilfe==3) { // Standardausgabe gewaehrleisten
  hhi.MusterVorgb();
 } else {
  hhi.VorgbSpeziell(); // die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void hhcl::VorgbSpeziell()" ueberladbar sind
  hhi.lieskonfein();
 } // if (hhi.obhilfe==3)
 hhi.lieszaehlerein(&hhi.aufrufe,&hhi.tagesaufr,&hhi.monatsaufr,&hhi.laufrtag);

 if (hhi.getcommandline())
  exit(8);
 if (hhi.obvi) hhi.dovi();
 if (hhi.zeigvers) {
   hhi.zeigversion();
 } // if (hhi.zeigvers)

 tuwas();
 hhi.autokonfschreib();
 hhi.schlussanzeige();
 return 0;
} // int main
