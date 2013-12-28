#include "stdafx.h"
#include <cpprest/http_client.h>
#include "HTTPClient.h"
#include "XMLHash.h"
#include "Deck.h"

std::string HTTPClient::GetSessionId(const std::string& i_access_token, const std::string& i_version, const XMLHash& i_check, bool& o_error, std::string& o_error_message) const
  {
  web::http::client::http_client client(U("http://tyrant.40in.net/api/sim/getSession"));

  web::json::value body_data;
  body_data[L"accessToken"] = web::json::value::string(utility::conversions::to_string_t(i_access_token));
  body_data[L"version"] = web::json::value::string(utility::conversions::to_string_t(i_version));

  web::json::value check;
  check[L"achievements"] = web::json::value::string(utility::conversions::to_string_t(i_check.GetAchievementsHash()));
  check[L"cards"] = web::json::value::string(utility::conversions::to_string_t(i_check.GetCardsHash()));
  check[L"missions"] = web::json::value::string(utility::conversions::to_string_t(i_check.GetMissionsHash()));
  check[L"quests"] = web::json::value::string(utility::conversions::to_string_t(i_check.GetQuestsHash()));
  check[L"raids"] = web::json::value::string(utility::conversions::to_string_t(i_check.GetRaidsHash()));

  body_data[L"check"] = check;

  o_error = false;
  std::string result;
  client.request(web::http::methods::POST, U(""), body_data).then(
    [&o_error, &result, &o_error_message](pplx::task<web::http::http_response> i_task)
      {
      try
        {
        i_task.get().extract_json().then(
          [&o_error, &result, &o_error_message](pplx::task<web::json::value> i_task)
            {
            try
              {
              auto json = i_task.get();
              if (json.has_field(L"sessId"))
                {
                result = utility::conversions::to_utf8string(json[L"sessId"].as_string());
                }
              else
                {
                o_error = true;
                o_error_message = "Error " + std::to_string(json[L"errorCode"].as_integer()) + ": " + utility::conversions::to_utf8string(json[L"error"].as_string());
                }
              }
            catch (...)
              {
              o_error = true;
              o_error_message = "Wrong JSON response from Fansite";
              }
            }).wait();
        }
      catch(...)
        {
        o_error = true;
        o_error_message = "Error when connecting to Fansite";
        }
      }).wait();
  return result;
  }

std::vector<Deck> HTTPClient::GetDecks(unsigned short i_limit, const std::string& i_session_id, bool& o_error, std::string& o_error_message) const
  {
  web::http::client::http_client client(U("http://tyrant.40in.net/api/sim/getDecks"));

  web::json::value body_data;
  body_data[L"sessId"] = web::json::value::string(utility::conversions::to_string_t(i_session_id));
  body_data[L"limit"] = web::json::value(i_limit);

  o_error = false;
  std::vector<Deck> result;
  client.request(web::http::methods::POST, U(""), body_data).then(
    [&o_error, &result, &o_error_message](pplx::task<web::http::http_response> i_task)
      {
      try
        {
        i_task.get().extract_json().then(
          [&o_error, &result, &o_error_message](pplx::task<web::json::value> i_task)
            {
            try
              {
              auto json_array = i_task.get();
              if (json_array.has_field(L"error"))
                {
                o_error = true;
                o_error_message = "Error " + std::to_string(json_array[L"errorCode"].as_integer()) + ": " + utility::conversions::to_utf8string(json_array[L"error"].as_string());
                return;
                }
              for (auto json_pair : json_array)
                {
                auto json = json_pair.second;
                std::vector<std::string> attacking_cards;
                for (auto json_card : json[L"attackingDeckCards"])
                  attacking_cards.push_back(utility::conversions::to_utf8string(json_card.second.as_string()));
                result.push_back(Deck(utility::conversions::to_utf8string(json[L"attackingDeck"].as_string())
                                    , std::move(attacking_cards)
                                    , json[L"isDelayed"].as_bool()
                                    , json[L"isOrdered"].as_bool()
                                    , json[L"isSurge"].as_bool()
                                    , static_cast<Deck::EDeckType>(json[L"type"].as_integer())
                                    , utility::conversions::to_utf8string(json[L"deckId"].as_string())));
                if (json.has_field(L"achId"))
                  result.back().SetAchievementId(json[L"achId"].as_integer());
                if (json.has_field(L"battlegroundId"))
                  result.back().SetBattlegroundId(json[L"battlegroundId"].as_integer());
                if (json.has_field(L"defendingDeck"))
                  result.back().SetDefendingDeck(utility::conversions::to_utf8string(json[L"defendingDeck"].as_string()));
                if (json.has_field(L"defendingDeckCards"))
                  {
                  std::vector<std::string> defending_cards;
                  for (auto json_card : json[L"defendingDeckCards"])
                    defending_cards.push_back(utility::conversions::to_utf8string(json_card.second.as_string()));
                  result.back().SetDefendingDeckCards(std::move(defending_cards));
                  }
                if (json.has_field(L"missionId"))
                  result.back().SetMissionId(json[L"missionId"].as_integer());
                if (json.has_field(L"questId"))
                  result.back().SetQuestId(json[L"questId"].as_integer());
                if (json.has_field(L"raidId"))
                  result.back().SetRaidId(json[L"raidId"].as_integer());
                }
              }
            catch (...)
              {
              o_error = true;
              o_error_message = "Wrong JSON response from Fansite";
              }
            }).wait();
        }
      catch(...)
        {
        o_error = true;
        o_error_message = "Error when connecting to Fansite";
        }
      }).wait();
  return result;
  }

bool HTTPClient::SubmitSimulation(const std::string& i_deck_id, const std::string& i_session_id, double i_ard, unsigned i_battles_total, unsigned i_battles_won, unsigned i_time_taken, std::string& o_error_message) const
  {
  web::http::client::http_client client(U("http://tyrant.40in.net/api/sim/submitSimulation"));

  web::json::value body_data;
  body_data[L"deckId"] = web::json::value::string(utility::conversions::to_string_t(i_deck_id));
  body_data[L"sessId"] = web::json::value::string(utility::conversions::to_string_t(i_session_id));
  if (i_ard >= 0)
    body_data[L"ard"] = web::json::value(i_ard);
  body_data[L"battlesTotal"] = web::json::value(static_cast<int32_t>(i_battles_total));
  body_data[L"battlesWon"] = web::json::value(static_cast<int32_t>(i_battles_won));
  body_data[L"timeTaken"] = web::json::value(static_cast<int32_t>(i_time_taken));

  bool result = false;
  client.request(web::http::methods::POST, U(""), body_data).then(
    [&result, &i_deck_id, &o_error_message](pplx::task<web::http::http_response> i_task)
      {
      try
        {
        i_task.get().extract_json().then(
          [&result, &i_deck_id, &o_error_message](pplx::task<web::json::value> i_task)
            {
            try
              {
              auto json = i_task.get();
              if (json.has_field(L"deckId"))
                {
                if (i_deck_id == utility::conversions::to_utf8string(json[L"deckId"].as_string()))
                  result = true;
                else
                  o_error_message = "Wrong deckId";
                }
              else
                o_error_message = "Error " + std::to_string(json[L"errorCode"].as_integer()) + ": " + utility::conversions::to_utf8string(json[L"error"].as_string());
              }
            catch (...)
              {
              o_error_message = "Wrong JSON response from Fansite";
              }
            }).wait();
        }
      catch(...)
        {
        o_error_message = "Error when connecting to Fansite";
        }
      }).wait();
  return result;
  }