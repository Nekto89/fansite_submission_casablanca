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