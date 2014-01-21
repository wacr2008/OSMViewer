#include "kmlwriter.h"

void KmlWriter::addPoint(const int &id, const QString &name, const QPointF &coords)
{
    KmlFactory* factory = KmlFactory::GetFactory();
    CoordinatesPtr coordinates = factory->CreateCoordinates();
    coordinates->add_latlng(coords.y(),coords.x());
    PointPtr point = factory->CreatePoint();
    point->set_coordinates(coordinates);

    StylePtr normal = factory->CreateStyle();
    normal->set_id("normal");
    IconStylePtr iconstyle = factory->CreateIconStyle();
    iconstyle->set_scale(0.6);
    normal->set_iconstyle(iconstyle);

    PlacemarkPtr placemark = factory->CreatePlacemark();
    placemark->set_description(name.toStdString());
    placemark->set_geometry(point);
    placemark->set_styleurl("#normal");

    // Serialize to XML
    QString xml = QString::fromStdString(kmldom::SerializePretty(placemark));

    // Print
    QFile _kmlFile(_kmlFileName);
    if (!_kmlFile.open(QIODevice::WriteOnly | QIODevice::Append))
        return;
    QTextStream out(&_kmlFile);
     out << xml;
}

KmlWriter::KmlWriter(QString name)
{
    _kmlFileName = name;
    QFile _kmlFile(_kmlFileName);
    if (!_kmlFile.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&_kmlFile);
    out<<"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
    out<<endl;
    out<<"<kml xmlns=\"http://www.opengis.net/kml/2.2\" >";
    out<<endl;
    out<<"<Document>";
    out<<endl;
    KmlFactory* factory = KmlFactory::GetFactory();
    kmldom::IconStyleIconPtr icon = factory->CreateIconStyleIcon();
    icon->set_href("root://icons/palette-4.png");
    StylePtr normal = factory->CreateStyle();
    normal->set_id("normal");
    IconStylePtr iconstyle = factory->CreateIconStyle();
    iconstyle->set_scale(0.6);
    iconstyle->set_icon(icon);
    normal->set_iconstyle(iconstyle);
    QString xml = QString::fromStdString(kmldom::SerializePretty(normal));
    out<<xml;

}


KmlWriter::~KmlWriter()
{
    QFile _kmlFile(_kmlFileName);
    if (!_kmlFile.open(QIODevice::WriteOnly | QIODevice::Append))
        return;
    QTextStream out(&_kmlFile);
    out<<"</Document>";
    out<<endl;
    out<<"</kml>";
    out<<endl;
}

