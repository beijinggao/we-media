if (self.CavalryLogger) { CavalryLogger.start_js(["B4MQQ"]); }

__d("isCdnURI",["CdnAkamaiDomainsConfig"],(function(a,b,c,d,e,f){"use strict";function a(a){if(a.getProtocol()!=="http"&&a.getProtocol()!=="https")return!1;var c=a.getPort();if(!!c&&c!==80&&c!==443)return!1;return a.isSubdomainOfDomain("fbcdn.net")?!0:b("CdnAkamaiDomainsConfig")[a.getDomain()]!=undefined}e.exports=a}),null);