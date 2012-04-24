class User < ActiveRecord::Base
  has_many :orders

  require 'net/https'
  require 'open-uri'
  require 'openssl'
  OpenSSL::SSL::VERIFY_PEER = OpenSSL::SSL::VERIFY_NONE

  def self.request_facebook_data(access_token)
    begin
      formattedURL="https://graph.facebook.com/me?access_token="+access_token+"&fields=third_party_id,email,name"
      url=URI.parse(formattedURL)
      responseJSON=open(url).read
      response=MultiJson.load(responseJSON)
      return response
    rescue OpenURI::HTTPError
      return false
    end
  end

  def self.login(fb_data)
    user = User.find_or_initialize_by_third_party_id(fb_data['third_party_id'])
    user.name = fb_data['name']
    user.email = fb_data['email']
    user.login_count += 1
    user.last_login = DateTime.now
    user.save
    return user
  end
end