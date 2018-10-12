if (self.CavalryLogger) { CavalryLogger.start_js(["GAkUQ"]); }

__d("isClickIDBlacklistSVDomainURI",["ClickIDDomainBlacklistSVConfig"],(function(a,b,c,d,e,f){"use strict";var g=["http","https"];function a(a){return!g.includes(a.getProtocol())?!1:b("ClickIDDomainBlacklistSVConfig").domains.some(function(b){return a.isSubdomainOfDomain(b)})}e.exports=a}),null);