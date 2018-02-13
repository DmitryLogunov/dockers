require './classes/factorial.rb'

class Application
  @@error = "The factorial number should be defined: /?number=xxx"

  def call(env)
    params = _parse_query_params env['QUERY_STRING']

    return _response @@error if params['number'] == nil ||  params['number'].to_i <= 0

    _response Factorial.new.calculate(params['number'])
  end

  private

  def _response(text)
    [200, {'Content-Type' => 'text/html'}, [text]]
  end

  def _parse_query_params(env_query_string)
    _response @@error if env_query_string == nil

    pare_hash = []
    params = {}

    env_query_string.split('&').each do |pare|
      pare_hash = pare.split('=')
      params[pare_hash[0]] = pare_hash[1].to_i
    end

    params
  end
end

run Application.new