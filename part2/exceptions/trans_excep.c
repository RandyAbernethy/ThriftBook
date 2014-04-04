//c_glib memory transport demo
//Build with: 
//gcc trans_excep.c `pkg-config --cflags thrift_c_glib --libs thrift_c_glib`
#include <stdio.h>
#include <thrift/c_glib/transport/thrift_memory_buffer.h>

struct Trade {
   char symbol[16];
   double price;
   int size;
};

int main(int argc, char ** argv) {
   GError *error = NULL;
   int result = 0;
   int size = (argc > 1) ? 5 : 1024;

   struct Trade trade;
   trade.symbol[0] = 'F'; trade.symbol[1] = '\0';
   trade.price = 13.10;
   trade.size = 2500;

   //Initialize glib type system and allocate an Apache Thrift Memory Transport
   g_type_init();
   ThriftMemoryBuffer *trans = g_object_new(THRIFT_TYPE_MEMORY_BUFFER, "buf_size", size, NULL);
   if (NULL == trans) {
      printf("Failed to create Memory Transport\n");
      return -1;
   }

   //Open the transport
   if (FALSE == thrift_memory_buffer_open(THRIFT_TRANSPORT(trans), &error)) {
      result = -1;
      printf("Open failed\n");
      if (NULL != error){
         printf(">> [%d]: %s\n", error->code, error->message);
         result = error->code;
         g_error_free(error);
      }
      g_object_unref(trans);
      return result;
   }

   //Write to the transport
   if (FALSE == thrift_memory_buffer_write(THRIFT_TRANSPORT(trans),
                                           (gpointer)&trade,
                                           sizeof(trade), 
                                           &error)) {
      result = -1;
      printf("Write failed\n");
      if (NULL != error){
         printf(">> [%d]: %s\n", error->code, error->message);
         result = error->code;
         g_error_free(error);
      }
      g_object_unref(trans);
      return result;
   }
   printf("Wrote Trade(%zu): %s %d @ %lf\n", sizeof(trade), trade.symbol, trade.size, trade.price);

   //Flush the transport
   if (FALSE == thrift_memory_buffer_flush(THRIFT_TRANSPORT(trans), &error)) {
      result = -1;
      printf("Flush failed\n");
      if (NULL != error){
         printf(">> [%d]: %s\n", error->code, error->message);
         result = error->code;
         g_error_free(error);
      }
      g_object_unref(trans);
      return result;
   }

   //Read a trade from the memory transport 
   if (sizeof(trade) != thrift_memory_buffer_read(THRIFT_TRANSPORT(trans), 
                                                  (gpointer)&trade,
                                                  sizeof(trade), 
                                                  &error)) {
      result = -1;
      printf("Read failed\n");
      if (NULL != error){
         printf(">> [%d]: %s\n", error->code, error->message);
         result = error->code;
         g_error_free(error);
      }
      g_object_unref(trans);
      return result;
   }
   printf("Read  Trade(%zu): %s %d @ %lf\n", sizeof(trade), trade.symbol, trade.size, trade.price);

   //Clean up
   thrift_memory_buffer_close(THRIFT_TRANSPORT(trans), &error);
   g_object_unref(trans);
   return 0;
}

