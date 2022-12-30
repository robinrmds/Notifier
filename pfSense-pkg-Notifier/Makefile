# $FreeBSD$

PORTNAME=	pfSense-pkg-Notifier
PORTVERSION=	0.1
PORTREVISION=	3
CATEGORIES=	sysutils
MASTER_SITES=	# empty
DISTFILES=	# empty
EXTRACT_ONLY=	# empty

MAINTAINER=	robin.rmds@gmail.com
COMMENT=	Notifier package

LICENSE=	APACHE20

NO_BUILD=	yes
NO_MTREE=	yes

SUB_FILES=	pkg-install pkg-deinstall 
SUB_LIST=	PORTNAME=${PORTNAME}

do-extract:
	${MKDIR} ${WRKSRC}


do-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/pkg
	${MKDIR} ${STAGEDIR}${PREFIX}/pkg/notifier
	${MKDIR} ${STAGEDIR}${PREFIX}/pkg/notifier/lib
	${MKDIR} ${STAGEDIR}/etc/inc/priv
	${MKDIR} ${STAGEDIR}${PREFIX}/www/packages/notifier
	${MKDIR} ${STAGEDIR}${DATADIR}
	${INSTALL_DATA}	-m 0644 ${FILESDIR}${PREFIX}/pkg/notifier.xml \
		${STAGEDIR}${PREFIX}/pkg
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/pkg/notifier.xml \
		${STAGEDIR}${PREFIX}/pkg
	install	-m 0755  ${FILESDIR}${PREFIX}/pkg/notifier/lib/telegram.sh \
		${STAGEDIR}${PREFIX}/pkg/notifier/lib
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/pkg/notifier.inc \
		${STAGEDIR}${PREFIX}/pkg
	${INSTALL_DATA} ${FILESDIR}/etc/inc/priv/notifier.priv.inc \
		${STAGEDIR}/etc/inc/priv
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/www/packages/notifier/notifier.php \
		${STAGEDIR}${PREFIX}/www/packages/notifier
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/www/packages/notifier/notifier_edit.php \
		${STAGEDIR}${PREFIX}/www/packages/notifier
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/www/packages/notifier/Brasil.png \
		${STAGEDIR}${PREFIX}/www/packages/notifier
	${INSTALL_DATA} ${FILESDIR}${PREFIX}/www/packages/notifier/index.php \
		${STAGEDIR}${PREFIX}/www/packages/notifier
	${INSTALL_DATA} ${FILESDIR}${DATADIR}/info.xml \
		${STAGEDIR}${DATADIR}
	@${REINPLACE_CMD} -i '' -e "s|%%PKGVERSION%%|${PKGVERSION}|" \
		${STAGEDIR}${PREFIX}/pkg/notifier.xml \
		${STAGEDIR}${DATADIR}/info.xml

.include <bsd.port.mk>
