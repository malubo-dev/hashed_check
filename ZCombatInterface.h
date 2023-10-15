#ifndef _ZCOMBATINTERFACE_H
#define _ZCOMBATINTERFACE_H

#include "ZInterface.h"
#include "MPicture.h"
#include "MEdit.h"
#include "MListBox.h"
#include "MLabel.h"
#include "MAnimation.h"
#include "ZObserver.h"
#include "ZCombatChat.h"
#include "ZCrossHair.h"
#include "ZMiniMap.h"
#include "ZVoteInterface.h"

_USING_NAMESPACE_REALSPACE2

class ZCharacter;
class ZScreenEffect;
class ZWeaponScreenEffect;
class ZMiniMap;
class ZCombatQuestScreen;

struct ZResultBoardItem {
	char szName[64];
	char szClan[CLAN_NAME_LENGTH];
	int nClanID;
	int nTeam;
	int nScore;
	int nKills;
	int nDeaths;
	int	nAllKill;
	int	nExcellent;
	int	nFantastic;
	int	nHeadShot;
	int	nUnbelievable;
	int	nDamageCaused;
	int	nDamageTaken;
	bool bMyChar;
	bool bGameRoomUser;

	ZResultBoardItem() { }
	ZResultBoardItem(const char *_szName, const char *_szClan, int _nTeam, int _nScore, int _nKills, int _nDeaths, bool _bMyChar = false, bool _bGameRoomUser = false) {
		strcpy(szName,_szName);
		strcpy(szClan,_szClan);
		nTeam = _nTeam;
		nScore = _nScore;
		nKills = _nKills;
		nDeaths = _nDeaths;
		// �ʿ��ϸ� �̰͵鵵 ������
		nAllKill = 0;
		nExcellent = 0;
		nFantastic = 0;
		nHeadShot = 0;
		nUnbelievable = 0;
		bMyChar = _bMyChar;
		bGameRoomUser = _bGameRoomUser;
	}
};

class ZResultBoardList : public list<ZResultBoardItem*>
{
public:
	void Destroy() { 
		while(!empty())
		{
			delete *begin();
			erase(begin());
		}
	}
};

struct DuelTournamentPlayer
{
	char m_szCharName[MATCHOBJECT_NAME_LENGTH];
	MUID uidPlayer;
	int m_nTP;
	int nVictory;
	int nMatchLevel;
	int nNumber;

	float fMaxHP;
	float fMaxAP;
	float fHP;
	float fAP;
};

class ZCombatInterface : public ZInterface
{
private:
	float				m_fElapsed;
protected:
	ZWeaponScreenEffect*		m_pWeaponScreenEffect;
//	ZScoreBoard*		m_pScoreBoard;

	// ���ȭ�鿡 �ʿ��Ѱ�
	ZScreenEffect*		m_pResultPanel;
	ZScreenEffect*		m_pResultPanel_Team;
	ZResultBoardList	m_ResultItems;
	ZScreenEffect*		m_pResultLeft;
	ZScreenEffect*		m_pResultRight;

	int					m_nClanIDRed;			///< Ŭ�����϶�
	int					m_nClanIDBlue;			///< �� Ŭ�� ID
	char				m_szRedClanName[32];	
	char				m_szBlueClanName[32];	///< �� Ŭ���� �̸�

	ZCombatQuestScreen*	m_pQuestScreen;

	ZBandiCapturer*		m_Capture;					///< ������ ĸ��...by kammir 2008.10.02
	bool				m_bShowUI;

	ZObserver			m_Observer;			///< ������ ���
	ZCrossHair			m_CrossHair;		///< ũ�ν� ���
	ZVoteInterface		m_VoteInterface;

	ZIDLResource*		m_pIDLResource;

	MLabel*				m_pTargetLabel;
	MBitmap*			m_ppIcons[ZCI_END];		/// Ī�� �����ܵ�
	MBitmapR2*			m_pResultBgImg;
	
	bool				m_bMenuVisible;
	
	bool				m_bPickTarget;
	char				m_szTargetName[256];		// crosshair target �̸�
	
	MMatchItemDesc*		m_pLastItemDesc;
	int					m_nBulletSpare;
	int					m_nBulletCurrMagazine;
	int					m_nMagazine;

	int					m_nBulletImageIndex;
	int					m_nMagazineImageIndex;

	char				m_szItemName[256];
	
	bool				m_bReserveFinish;
	unsigned long int	m_nReserveFinishTime;

	bool				m_bDrawLeaveBattle;
	int					m_nDrawLeaveBattleSeconds;

	bool				m_bOnFinish;
	bool				m_bShowResult;
	bool				m_bIsShowUI;					// ��� UI ���߱�... by kammir 20081020 (������ ���û���)
	bool				m_bSkipUIDrawByRule;			// ���ӷ��� �ʿ��ϴٸ� UI ��ο츦 �� �� �ֵ���

	bool				m_bDrawScoreBoard;
//	bool				m_bKickPlayerListVisible;		// ����ȭ�鿡 �÷��̾� ����Ʈ �����ش�

	float				m_fOrgMusicVolume;

	bool				m_bNetworkAlive;
	DWORD				m_dLastTimeTick;
	DWORD				m_dAbuseHandicapTick;

	void SetItemImageIndex(int nIndex);

	void SetItemName(const char* szName);
	void UpdateCombo(ZCharacter* pCharacter);
	
	void OnFinish();

	void GameCheckPickCharacter();

	// ȭ�鿡 �׸��°Ͱ� ���õ� ��ǵ�
	void IconRelative(MDrawContext* pDC,float x,float y,int nIcon);

	void DrawFriendName(MDrawContext* pDC);			// ������ �̸�
	void DrawEnemyName(MDrawContext* pDC);			// �� �̸�
	void DrawAllPlayerName(MDrawContext* pDC);		// ��� �� �̸� ǥ�� (Free Spectator)

	void DrawScoreBoard(MDrawContext* pDC);			// ���� ȭ�� (tabŰ)
	void DrawDuelTournamentScoreBoard(MDrawContext* pDC);						// ��� ��ʸ�Ʈ ����ǥ ȭ�� (tabŰ)
	void DrawPlayTime(MDrawContext* pDC, float xPos, float yPos);	// �÷��� �ð�
	void DrawResultBoard(MDrawContext* pDC);		// ���� ���ȭ��
	void DrawSoloSpawnTimeMessage(MDrawContext* pDC);	// ��� ������ Ÿ�̸� �޽���
	void DrawLeaveBattleTimeMessage(MDrawContext* pDC);	// ���ӿ��� ������ ��ٸ��� �ð�ǥ��
//	void DrawVoteMessage(MDrawContext* pDC);		// ��ǥ�� �������϶� �޽���
//	void DrawKickPlayerList(MDrawContext* pDC);		// kick �� �÷��̾� �����ϴ� ȭ��
	void GetResultInfo( void);

	void DrawTDMScore(MDrawContext* pDC);

	void DrawNPCName(MDrawContext* pDC);	// ����׿�

	void UpdateNetworkAlive(MDrawContext* pDC);

public:
	ZCombatChat			m_Chat;
	ZCombatChat			m_AdminMsg;
	DWORD				m_nReservedOutTime;				// Finish �Ŀ� ������ ������ �ð��� ����
	DWORD               m_lastDamageFloatingTime;


	ZCombatInterface(const char* szName=NULL, MWidget* pParent=NULL, MListener* pListener=NULL);
	virtual ~ZCombatInterface();

	void OnInvalidate();
	void OnRestore();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void OnDraw(MDrawContext* pDC);	// �׸��� ���������� ���� �׸���
	virtual void OnDrawCustom(MDrawContext* pDC);
	virtual void DrawAfterWidgets(MDrawContext* pDC);	//MWidget���� �������� �Լ�, UI ������ ��� �׸� �� ���� DC�� �߰��� �׸��� ���� �Լ�
	void		 DrawPont(MDrawContext* pDC);
	void		 DrawMyNamePont(MDrawContext* pDC);
	void		 DrawMyWeaponPont(MDrawContext* pDC);
	void		 DamageFloatingEffect(MDrawContext* pDC); // Float Damage
	void		 DmgFloat();
	void		 DrawScore(MDrawContext* pDC);
	void		 DrawBuffStatus(MDrawContext* pDC);
	void		 DrawFinish();
	int DrawVictory( MDrawContext* pDC, int x, int y, int nWinCount, bool bGetWidth = false);

	virtual bool IsDone();

	void OnAddCharacter(ZCharacter *pChar);

	void Resize(int w, int h);

	void OutputChatMsg(const char* szMsg);
	void OutputChatMsg(MCOLOR color, const char* szMsg);

	virtual bool OnEvent(MEvent* pEvent, MListener* pListener);

	static MFont *GetGameFont();
	MPOINT GetCrosshairPoint() { return MPOINT(MGetWorkspaceWidth()/2,MGetWorkspaceHeight()/2); }
	
	ZBandiCapturer*	GetBandiCapturer()			{ return m_Capture; }					///< ������ ĸ��...by kammir 2008.10.02

	void ShowMenu(bool bVisible = true);
	void ShowInfo(bool bVisible = true);
	void EnableInputChat(bool bInput=true, bool bTeamChat=false);

	void SetDrawLeaveBattle(bool bShow, int nSeconds);

	void ShowChatOutput(bool bShow);
	bool IsChat() { return m_Chat.IsChat(); }
	bool IsTeamChat() { return m_Chat.IsTeamChat(); }
	bool IsMenuVisible() { return m_bMenuVisible; }

	void Update(float fElapsed);
	void SetPickTarget(bool bPick, ZCharacter* pCharacter = NULL);

//	void ShowScoreBoard(bool bVisible = true);
//	bool IsScoreBoardVisible() { return m_pScoreBoard->IsVisible(); }

	void Finish();
	bool IsFinish();

	ZCharacter* GetTargetCharacter();
	MUID		GetTargetUID();

	int GetPlayTime();

	void SetObserverMode(bool bEnable);
	bool GetObserverMode() { return m_Observer.IsVisible(); }
	ZObserver* GetObserver() { return &m_Observer; }
	ZCrossHair* GetCrossHair() { return &m_CrossHair; }

	ZVoteInterface* GetVoteInterface()	{ return &m_VoteInterface; }

	void ShowCrossHair(bool bVisible) {	m_CrossHair.Show(bVisible); 	}
	void OnGadget(MMatchWeaponType nWeaponType);
	void OnGadgetOff();

	void SetSkipUIDraw(bool b) { m_bSkipUIDrawByRule = b; }
	bool IsSkupUIDraw() { return m_bSkipUIDrawByRule; }

	bool IsShowResult( void)  { return m_bShowResult; }
	bool IsShowUI( void)  { return m_bIsShowUI; }
	void SetIsShowUI(bool bIsShowUI)  { m_bIsShowUI = bIsShowUI; }
	bool IsShowScoreBoard()   { return m_bDrawScoreBoard; }
//	void SetKickPlayerListVisible(bool bShow = true) { m_bKickPlayerListVisible = bShow; }
//	bool IsKickPlayerListVisible() { return m_bKickPlayerListVisible; }

	bool IsNetworkalive()	{ return m_bNetworkAlive; }

	const char* GetRedClanName() const { return m_szRedClanName; }
	const char* GetBlueClanName() const { return m_szBlueClanName; }
};

void TextRelative(MDrawContext* pDC,float x,float y,const char *szText,bool bCenter=false);

#endif