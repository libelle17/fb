#define DPROG "fb"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_pvirtnachrueckfragen,
	T_pvirtfuehraus,
	T_in_pvirtfuehraus_pidw,
	T_virttesterg,
	T_virtzeigversion,
	T_virtzeigueberschrift, 
	T_Fuege_ein, //ω
	T_VorgbAllg,
	T_VorgbSpeziell,
	T_MusterVorgb,
	T_fbusr_k,
	T_fbusr_l,
	T_fbpwd_k,
	T_fbpwd_l,
	T_verwendet_fuer_die_Fritzbox_den_Benutzer_string_anstatt,
	T_verwendet_fuer_die_Fritzbox_das_Passwort_string,
	T_Fritzbox_Benutzer,
	T_Fritzbox_Passwort,
	T_Ermittelt_die_moeglichen_Tr_064_Befehle_und_zeigt_sie_an,
	T_MAX //α
}; // enum T_ //ω
//α
class hhcl:public hcl
{
	private: 
		svec fbip; // Fritzbox-IP
		uchar anhl{0};    // <DPROG> anhalten
		string dszahl{"30"}; // Datensatzzahl fuer Tabellenausgaben
		uchar obvi=0; // ob Konfigurationsdatei editiert werden soll
		string fbusr; // User für Fritzbox
		string fbpwd; // Password für Fritzbox
		//ω
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista{0};
		long listz{30}; //ω
	public: //α //ω
	private: //α //ω
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=string());
		void pvirtvorrueckfragen();
		void virtrueckfragen();
		void neurf();
		void pvirtnachvi();
		void pvirtnachrueckfragen();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void loeschenix();
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
}; // class hhcl //ω
