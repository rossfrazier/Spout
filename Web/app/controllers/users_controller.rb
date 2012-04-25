class UsersController < ApplicationController
  def login
    redirect_url = session[:redirect_after_login] || drinks_path
    reset_session
    session[:redirect_after_login] = redirect_url

    render :layout=>'authentication'
  end

  def authenticate
    response = User.request_facebook_data(params["accessToken"])
    if response
      if user = User.login(response)
        session[:user_id] = user.id
        flash[:success] = "Logged in."
        redirect_url = session[:redirect_after_login]
        session[:redirect_after_login] = nil
        redirect_after_login(redirect_url)
      end
    else
      flash[:error] = "There was a problem."
      render :js=>'window.location="'+users_login_path+'"' and return
    end
  end

  def show
    @machine = Machine.first
    @users = User.all
  end

  def edit

  end

  def update

  end
end
