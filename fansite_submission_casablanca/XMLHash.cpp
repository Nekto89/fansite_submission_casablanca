#include "stdafx.h"
#include "XMLHash.h"

#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX

std::string XMLHash::_MD5(const std::string& i_input) const
  {
	unsigned long long CryptProv; 
	unsigned long long CryptHash; 
	unsigned char BytesHash[33];
	unsigned long dwHashLen;
	std::string final;

	if(CryptAcquireContext(&CryptProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_MACHINE_KEYSET)
    && CryptCreateHash(CryptProv, CALG_MD5, 0, 0, &CryptHash)
    && CryptHashData(CryptHash, reinterpret_cast<const unsigned char*>(&i_input[0]), static_cast<unsigned long>(i_input.length()), 0)
    && CryptGetHashParam(CryptHash, HP_HASHVAL, BytesHash, &dwHashLen, 0))
		{
    final.reserve(32);
		std::string hexcharset = "0123456789abcdef";
		for(unsigned char i = 0; i != 16; ++i)
			{
      final += hexcharset[(BytesHash[i] >> 4) & 0xF];
			final += hexcharset[BytesHash[i] & 0x0F];
			}
		}
	CryptDestroyHash(CryptHash); 
	CryptReleaseContext(CryptProv, 0); 
	return final; 
  }

XMLHash::XMLHash(std::istream& i_achievements, std::istream& i_cards, std::istream& i_missions, std::istream& i_quests, std::istream& i_raids)
  : m_achievements(_MD5(std::string(std::istreambuf_iterator<char>(i_achievements), std::istreambuf_iterator<char>())))
  , m_cards(_MD5(std::string(std::istreambuf_iterator<char>(i_cards), std::istreambuf_iterator<char>())))
  , m_missions(_MD5(std::string(std::istreambuf_iterator<char>(i_missions), std::istreambuf_iterator<char>())))
  , m_quests(_MD5(std::string(std::istreambuf_iterator<char>(i_quests), std::istreambuf_iterator<char>())))
  , m_raids(_MD5(std::string(std::istreambuf_iterator<char>(i_raids), std::istreambuf_iterator<char>())))
  {
  }

const std::string& XMLHash::GetAchievementsHash() const
  {
  return m_achievements;
  }

const std::string& XMLHash::GetCardsHash() const
  {
  return m_cards;
  }

const std::string& XMLHash::GetMissionsHash() const
  {
  return m_missions;
  }

const std::string& XMLHash::GetQuestsHash() const
  {
  return m_quests;
  }

const std::string& XMLHash::GetRaidsHash() const
  {
  return m_raids;
  }