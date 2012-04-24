class ApplicationController < ActionController::Base
  protect_from_forgery

  private
  helper_method :authenticate!,
                :current_user,
                :user_signed_in?,
                :user_signed_out?,
                :redirect_after_login

  def authenticate!
    unless user_signed_in?
      session[:redirect_after_login]=request.url
      flash[:error] = "You can sign in through Facebook to access this app."
      redirect_to login_users_path
    end
  end

  def current_user
    if session[:user_id]
      @current_user ||= User.find(session[:user_id])
      return @current_user
    else
      return false
    end
  end

  def user_signed_in?
    !!current_user
  end

  def user_signed_out?
    !current_user
  end

  def redirect_after_login(url)
    if request.xhr?
      render :js => "window.location='"+url+"'" and return
    else
      redirect_to url and return
    end
  end

end
