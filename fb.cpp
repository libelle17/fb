// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "fb.h"
#include "tr64.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]=
{
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_pvirtvorpruefggfmehrfach,
	{"pvirtvorpruefggfmehrfach()","pvirtbeforecheckmultiple()"},
	// T_pvirtfuehraus,
	{"pvirtfuehraus()","pvirtexecute()"},
	// T_in_pvirtfuehraus_pidw,
	{"in pvirtfuehraus(), pidw","in pvirtexecute(), pidw"},
	// T_virttesterg,
	{"virttesterg()","virtcheckresult()"},
	// T_virtzeigversion,
	{"virtzeigversion()","virtshowversion()"},
	// T_virtzeigueberschrift, 
	{"virtzeigueberschrift()","virtshowheadline()"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_VorgbAllg
	{"VorgbAllg()","generalprefs()"},
	// T_VorgbSpeziell
	{"VorgbSpeziell()","specialprefs()"},
	// T_MusterVorgb
	{"MusterVorgb()","sampleprefs"},
	// T_rueckfragen
	{"rueckfragen()","callbacks()"},
	// T_fbusr_k,
	{"fbusr","fbusr"},
	// T_fbusr_l,
	{"fbusr","fbusr"},
	// T_fbpwd_k,
	{"fbpwd","fbpwd"},
	// T_fbpwd_l,
	{"fbpwd","fbpwd"},
	// T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt
	{"verwendet fuer die Fritzbox den Benutzer <string> anstatt","takes the user <string> for the fritzbox instead of"},
	// T_verwendet_fuer_die_Fritzbox_das_Passwort_string
	{"verwendet fuer die Fritzbox das Passwort <string>","takes the password <string< for the fritzbox"},
	// T_Fritzbox_Benutzer
	{"Fritzbox-Benutzer","fritzbox user"},
	// T_Fritzbox_Passwort
	{"Fritzbox-Passwort","fritzbox password"},
	// T_Ermittelt_die_moeglichen_Tr_064_Befehle_und_zeigt_sie_an,
	{"Ermittelt die möglichen Tr-064-Befehle der verwendeten Fritzbox und zeigt sie an.",
		"Finds out the possible Tr-064 commands of the current fritzbox and displays them."},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw; // wird zweimal verwendet, um auf Kindprozesse zu warten: in wegfaxen (auf die Faxarten) und in pvirtfueraus (auf korrigierefbox, -capi und -hyla
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

using namespace std; //ω
hhcl::hhcl(const int argc, const char *const *const argv):hcl(argc,argv,DPROG,/*mitcron*/0) //α
{
	hLog(violetts+"hhcl::hhcl()"+schwarz);
	// mitpids=1;
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	hcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
} // void hhcl::pvirtVorgbSpeziell

// aufgerufen in lauf
void hhcl::virtinitopt()
{
	hLog(violetts+"virtinitopt()"+schwarz); //ω
	opn<<new optcl(/*pptr*/&anhl,/*art*/puchar,T_st_k,T_stop_l,/*TxBp*/&Tx,/*Txi*/T_DPROG_anhalten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	opn<<new optcl(/*pname*/"fbusr",/*pptr*/&fbusr,/*art*/pstri,T_fbusr_k,T_fbusr_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,/*wi*/1,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/1);
	opn<<new optcl(/*pname*/"fbpwd",/*pptr*/&fbpwd,/*art*/ppwd,T_fbpwd_k,T_fbpwd_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_die_Fritzbox_das_Passwort_string,/*wi*/1,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/1);
	hcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
	erkl<<blau<<Tx[T_Ermittelt_die_moeglichen_Tr_064_Befehle_und_zeigt_sie_an]<<schwarz;
} // void hhcl::pvirtmacherkl //α
//ω
//α

// aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	hcl::virtMusterVorgb(); //α
} // void hhcl::MusterVorgb

// aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler //α
//ω
// aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=string()*/)
{
	hLog(violetts+Tx[T_virtzeigversion]+schwarz);
	hcl::virtzeigversion(ltiffv);  //ω
} // void hhcl::virtzeigversion //α
//ω
//α
// aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
} // void hhcl::pvirtvorrueckfragen //α

void hhcl::neurf()
{
	for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
		omit--;
		if ((*omit)->Txrf!=-1) {
		 const char* const text=(*(*omit)->TxBp)[(*omit)->Txrf];
		cout<<text<<endl;
		}
	}
} // void hhcl::neurf
 //ω
// aufgerufen in lauf //α
void hhcl::virtrueckfragen()
{
	hLog(violetts+Tx[T_virtrueckfragen]+", rzf: "+blau+ltoan(rzf)+schwarz);
	if (fbusr.empty() || fbpwd.empty()) rzf=1;
	if (rzf) { //ω
		fbusr=Tippstr(Tx[T_Fritzbox_Benutzer],&fbusr);
		fbpwd.clear();
		do {
			fbpwd=Tippstr(string(Tx[T_Fritzbox_Passwort])+Txk[T_fuer_Benutzer]+dblau+fbusr+schwarz+"'"/*,&smtppwd*/);
			fbpwd=Tippstr(string(Tx[T_Fritzbox_Passwort])+Txk[T_fuer_Benutzer]+dblau+fbusr+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")"/*,&mpw2*/);
		} while (fbpwd!=fbpwd);
	} // if (rzf) //α
	hcl::virtrueckfragen();
	//// opn.oausgeb(rot);
} // void hhcl::virtrueckfragen
//ω
//α
// aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	hLog(violetts+Tx[T_virtpruefweiteres]+schwarz); //ω
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ 
	hLog(violetts+Tx[T_virtzeigueberschrift]+schwarz); //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
//α
// Parameter -st / --stop
// aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
} // void hhcl::anhalten() //α
//ω
//α
void hhcl::pvirtnachvi()
{ //ω
} //α

// aufgerufen in lauf
void hhcl::pvirtvorpruefggfmehrfach()
{
	hLog(violetts+Tx[T_pvirtvorpruefggfmehrfach]+schwarz);
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
} // void hhcl::pvirtvorpruefggfmehrfach //α
//ω

int tuwas()
{
	tr64cl tr64("libelle17","bach17raga");
//	tr64cl tr64("","");
	string buffer;
	string kopfi[]={"deviceType","friendlyName","manufacturer","manufacturerURL","modelDescription","modelName","modelNumber","modelURL","UDN"};
	string grund="http://fritz.box:49000";
	holurl(grund+"/tr64desc.xml",&buffer);
	size_t pos=0;
	string serviceh;
	int zeigalle=0;
	mdatei logf("fbausg.txt",ios::out,0);
	int oblog=logf.is_open();
	for(size_t ind=0;ind<sizeof kopfi/sizeof *kopfi;ind++) {
		string kbuf;
		holraus(buffer,kopfi[ind],&kbuf);
		if (zeigalle) {
			caus<<"  "<<kopfi[ind]<<": "<<rot<<kbuf<<schwarz<<endl;
		}
		if (oblog) logf<<"  "<<kopfi[ind]<<": "<<kbuf<<endl;
	}
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
			string ubuf;
			int obtr64=0;
			if (keinin && action.find("Get")!=string::npos) {
				obtr64=1;
				tr64.fragurl(controlURL,serviceType,action,&ubuf);
				/*
			} else if (action=="GetSpecificDeviceInfos") {
				obtr64=1;
				svec iname; iname<<"NewAIN";
				svec ival; ival<<"0";
				tr64.fragurl(controlURL,serviceType,action,&ubuf,&iname,&ival);
				cout<<violett<<ubuf<<schwarz<<endl;
				exit(0);
				*/
				/*
					 // controlURL: /upnp/control/x_voip
					 // serviceType: urn:dslforum-org:service:X_VoIP:1
					 // action:      X_AVM-DE_DialNumber
			} else if (action=="X_AVM-DE_DialNumber") {
				obtr64=1;
				svec iname; iname<<"NewX_AVM-DE_PhoneNumber";
				svec ival; ival<<"#96*2*";
				tr64.fragurl(controlURL,serviceType,action,&ubuf,&iname,&ival);
				cout<<violett<<ubuf<<schwarz<<endl;
				exit(0);
				*/
			}
			if (obtr64) {
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


void hhcl::pvirtfuehraus() //α
{ 
	hLog(violetts+Tx[T_pvirtfuehraus]+schwarz); //ω
	tuwas();
} // void hhcl::pvirtfuehraus  //α

// aufgerufen in lauf
void hhcl::virtschlussanzeige()
{  
	hLog(violetts+Txk[T_virtschlussanzeige]+schwarz); //ω
	hcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige
 
// aufgerufen in: main und pruefcapi
void hhcl::virtautokonfschreib()
{
//// const int altobverb=obverb; obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat)) {
		caus<<"Setze obzuschreib, da "<<akonfdt<<" nicht da"<<endl;
		hccd.obzuschreib=1;
	}
	if (rzf||hccd.obzuschreib||kschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
    obverb=2;
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
//// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
////	const int altobverb{obverb}; obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz); //ω
	hcl::virtlieskonfein(); //α //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
////	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω
int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
	hLog(violetts+Txk[T_virttesterg]+schwarz);
} //ω
