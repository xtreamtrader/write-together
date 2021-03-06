#include <cte/client/client.h>
#include <QtCore/QPointer>
#include <QtCore/QThread>

namespace cte {
    Client::Client() {
        // create workers
        ui_worker_ = QSharedPointer<UiWorker>::create();
        network_worker_ = QSharedPointer<NetworkWorker>::create();

        // connect workers
        NetworkWorker *network_worker = network_worker_.data();
        UiWorker *ui_worker = ui_worker_.data();
        connect(ui_worker, &UiWorker::connection_request, network_worker, &NetworkWorker::set_server);
        connect(ui_worker, &UiWorker::new_message, network_worker, &NetworkWorker::send_message);
        connect(network_worker, &NetworkWorker::connected, ui_worker, &UiWorker::show_login_form);
        connect(network_worker, &NetworkWorker::new_message, ui_worker, &UiWorker::process_message);
        connect(network_worker, qOverload<const QString&>(&NetworkWorker::error_occurred),
                ui_worker, &UiWorker::show_connection_form);
        connect(network_worker, qOverload<const QString&>(&NetworkWorker::error_occurred),
                ui_worker, qOverload<const QString&>(&UiWorker::show_error));
    }

    void Client::start(const QString &hostname, int port) {
        ui_worker_->show_connection_loading(hostname, port);
        network_worker_->set_server(hostname, port);
    }
}
